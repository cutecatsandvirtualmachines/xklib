#include "memory.h"

last_pt_t get_last_pt(unsigned long addr)
{
	last_pt_t last_pt = { 0 };
	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *pte;
	struct mm_struct *mm = current->mm;
	pgd = pgd_offset(mm, addr);
	if (INVALID_PGD(pgd))
		goto end;

	pud = pud_offset(pgd, addr);
	if (INVALID_PUD(pud))
		goto end;

	pmd = pmd_offset(pud, addr);
	if (INVALID_PMD(pmd))
		goto end;

	if (pmd_trans_huge(*pmd)) {
		last_pt.pt_type = pt_type_pmd;
		last_pt.pmd = *pmd;
		goto end;
	}
	pte = pte_offset_kernel(pmd, addr);
	if (INVALID_PTE(pte))
		goto end;

	last_pt.pt_type = pt_type_pte;
	last_pt.pte = *pte;
	return last_pt;
end:
	last_pt.pt_type = pt_type_invalid;
	return last_pt;
}

void map_pdpte(pml4e_64 *ppml4e, unsigned long addr,
	       struct pt_permissions perms, virt_addr_map *paddr_map)
{
	const u64 table_idx = 0;

	pml4e_64 pml4e = { 0 };
	pdpte_64 *ppdpte = kmalloc(PAGE_SIZE, GFP_KERNEL);
	memset(ppdpte, 0, PAGE_SIZE);

	paddr_map->level3 = table_idx;
	map_pmd(ppdpte, addr, perms, paddr_map);

	//Must atomically set page table flags
	pml4e.flags = ppml4e->flags;
	pml4e.present = 1;
	pml4e.write = perms.write;
	pml4e.executedisable = !perms.exec;
	pml4e.supervisor = MAP_ALLOW_USER_ACCESS;
	pml4e.pageframenumber = PAGE_ALIGN(virt_to_phys(ppdpte)) >> PAGE_SHIFT;
	pml4e.ignored1 = 3;
	ppml4e->flags = pml4e.flags;
}

void map_pde(pdpte_64 *ppdpte, unsigned long addr, struct pt_permissions perms,
	     virt_addr_map *paddr_map)
{
	const u64 table_idx = 0;

	pdpte_64 pdpte = { 0 };
	pde_64 *ppde = kmalloc(PAGE_SIZE, GFP_KERNEL);
	memset(ppde, 0, PAGE_SIZE);

	paddr_map->level2 = table_idx;
	map_pte(ppde, addr, perms, paddr_map);
	pdpte.flags = ppdpte->flags;

	pdpte.present = true;
	pdpte.write = perms.write;
	pdpte.executedisable = !perms.exec;
	pdpte.supervisor = MAP_ALLOW_USER_ACCESS;
	pdpte.pageframenumber = PAGE_ALIGN(virt_to_phys(ppde)) >> PAGE_SHIFT;
	pdpte.ignored1 = 3;
	ppdpte->flags = pdpte.flags;
}

void map_pte(pde_64 *ppde, unsigned long addr, struct pt_permissions perms,
	     virt_addr_map *paddr_map)
{
	const u64 table_idx = 0;

	pde_64 pde = { 0 };
	pte_64 *ppte = kmalloc(PAGE_SIZE, GFP_KERNEL);
	memset(ppte, 0, PAGE_SIZE);

	paddr_map->level1 = table_idx;
	fill_pte(ppte, addr, perms, paddr_map);
	pde.flags = ppde->flags;

	pde.present = true;
	pde.write = perms.write;
	pde.executedisable = !perms.exec;
	pde.supervisor = MAP_ALLOW_USER_ACCESS;
	pde.pageframenumber = PAGE_ALIGN(virt_to_phys(ppte)) >> PAGE_SHIFT;
	pde.ignored1 = 3;
	ppde->flags = pde.flags;
}

void fill_pte(pte_64 *ppte, unsigned long addr, struct pt_permissions perms,
	      virt_addr_map *paddr_map)
{
	pte_64 pte = { 0 };

	pte.flags = ppte->flags;
	pte.present = true;
	pte.write = perms.write;
	pte.executedisable = !perms.exec;
	pte.supervisor = MAP_ALLOW_USER_ACCESS;
	pte.pageframenumber = PAGE_ALIGN(addr) >> PAGE_SHIFT;
	ppte->flags = pte.flags;

	paddr_map->offset = addr & ~PAGE_MASK;
}

u64 find_free_pud(pud_t *ppud)
{
	for (int i = 0; i < PT_MAX; i++) {
		if (INVALID_PUD(&ppud[i]))
			return i;
	}
	return PT_INVALID;
}

u64 find_free_pmd(pmd_t *ppmd)
{
	for (int i = 0; i < PT_MAX; i++) {
		if (INVALID_PMD(&ppmd[i]))
			return i;
	}
	return PT_INVALID;
}

u64 find_free_pte(pte_t *ppte)
{
	for (int i = 0; i < PT_MAX; i++) {
		if (INVALID_PTE(&ppte[i]))
			return i;
	}
	return PT_INVALID;
}

void *map_physical(unsigned long addr, struct pt_permissions perms)
{
	struct pml4t *ppml4t = kmalloc_struct(ppml4t);
	virt_addr_map addr_map = { 0 };
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	struct mm_struct *mm = current->mm;

	addr_map.signext = 0xffff;
	addr_map.level4 = ROOT_MAP_INDEX;

	pgd = PGD;
	pgd = &pgd[ROOT_MAP_INDEX];
	if (unlikely(INVALID_PGD(pgd))) {
		map_pud(pgd, addr, perms, &addr_map);
		goto end;
	}

	pud = phys_to_virt(pgd_pfn(*pgd) * PAGE_SIZE);
	int pud_idx = find_free_pud(pud);
	if (unlikely(pud_idx == PT_INVALID)) {
		dbg_msg("no more free pud indexes at: 0x%llx", pud);
		addr_map.flags = 0;
		goto end;
	}
	addr_map.level3 = pud_idx;
	pud = &pud[pud_idx];
	if (unlikely(!XKLIB_PT(pud))) {
		map_pmd(pud, addr, perms, &addr_map);
		goto end;
	}

	pmd = phys_to_virt(pud_pfn(*pud) * PAGE_SIZE);
	int pmd_idx = find_free_pmd(pmd);
	if (unlikely(pmd_idx == PT_INVALID)) {
		dbg_msg("no more free pmd indexes at: 0x%llx", pmd);
		addr_map.flags = 0;
		goto end;
	}
	addr_map.level2 = pmd_idx;
	pmd = &pmd[pmd_idx];
	if (unlikely(!XKLIB_PT(pmd))) {
		map_pte(pmd, addr, perms, &addr_map);
		goto end;
	}

	pte = phys_to_virt(pmd_pfn(*pmd) * PAGE_SIZE);
	int pte_idx = find_free_pte(pte);
	if (unlikely(pte_idx == PT_INVALID)) {
		dbg_msg("no more free pte indexes at: 0x%llx", pte);
		addr_map.flags = 0;
		goto end;
	}
	addr_map.level1 = pte_idx;
	pte = &pte[pte_idx];
	fill_pte(pte, addr, perms, &addr_map);

end:
	return (void *)addr_map.flags;
}

bool page_mapping_exist(unsigned long addr)
{
	last_pt_t last_pt;
	last_pt = get_last_pt(addr);
	if (unlikely(last_pt.pt_type == pt_type_invalid))
		return false;
	return true;
}