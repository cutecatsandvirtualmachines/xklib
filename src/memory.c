#include "memory.h"

last_pt_t get_last_pt(unsigned long addr)
{
	last_pt_t last_pt;
	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *pte;
	struct mm_struct *mm = current->mm;
	pgd = pgd_offset(mm, addr);
	if (unlikely(!pgd) || unlikely(pgd_none(*pgd)) ||
	    unlikely(!pgd_present(*pgd)))
		goto end;

	pud = pud_offset(pgd, addr);
	if (unlikely(!pud) || unlikely(pud_none(*pud)) ||
	    unlikely(!pud_present(*pud)))
		goto end;

	pmd = pmd_offset(pud, addr);
	if (unlikely(!pmd) || unlikely(pmd_none(*pmd)) ||
	    unlikely(!pmd_present(*pmd)))
		goto end;

	if (pmd_trans_huge(*pmd)) {
		last_pt.pt_type = pt_type_pmd;
		last_pt.value.pmd = *pmd;
		goto end;
	}
	pte = pte_offset_kernel(pmd, addr);
	if (unlikely(!pte) || unlikely(!pte_present(*pte)))
		goto end;

	last_pt.pt_type = pt_type_pte;
	last_pt.value.pte = *pte;
	return last_pt;
end:
	last_pt.pt_type = pt_type_invalid;
	return last_pt;
}

bool page_mapping_exist(unsigned long addr)
{
	last_pt_t last_pt;
	last_pt = get_last_pt(addr);
	if (unlikely(last_pt.pt_type == pt_type_invalid))
		return false;
	return true;
}