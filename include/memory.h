#include <asm/io.h>
#include <asm/page_64_types.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#include "debug.h"
#include "ia32.h"
#include "xstdint.h"

/**
 * IMPORTANT:
 * All allocations in this unit must use kmalloc for portability with
 * virt_to_phys
 */

#define INVALID_PGD(pgd) (!((pml4e_64 *)pgd)->present)

#define INVALID_PUD(pud) (!((pdpte_64 *)pud)->present)

#define INVALID_PMD(pmd) (!((pde_64 *)pmd)->present)

#define INVALID_PTE(pte) (!((pte_64 *)pte)->present)

#define XKLIB_PT(pt) (((pde_64 *)pt)->ignored1 == 3)

#define PGD pgd_offset(mm, 0)
#define PUD pud_offset(PGD, 0)
#define PMD pmd_offset(PUD, 0)

#define ROOT_MAP_INDEX 470
#define PT_MAX 512
#define PT_INVALID (-1ull)

//Mapped page tables will be marked user accessible even if in kernel
#define MAP_ALLOW_USER_ACCESS 0

#define kmalloc_struct(var) kmalloc(sizeof(var), GFP_KERNEL)

#define map_pud map_pdpte
#define map_pmd map_pde

struct pt_permissions {
	u64 read : 1;
	u64 write : 1;
	u64 exec : 1;
};

struct pml4t {
	pgd_t entry[PT_MAX];
};

struct pdpt {
	pmd_t entry[PT_MAX];
};

struct pdt {
	pud_t entry[PT_MAX];
};

struct pt {
	pte_t entry[PT_MAX];
};

typedef union {
	struct {
		u64 offset : 12;
		u64 level1 : 9;
		u64 level2 : 9;
		u64 level3 : 9;
		u64 level4 : 9;
		u64 signext : 16;
	};

	u64 flags;
} virt_addr_map, *pvirt_addr_map;

enum last_pt_type { pt_type_invalid, pt_type_pte, pt_type_pmd };

typedef struct _last_pt_t {
	union {
		pte_t pte;
		pmd_t pmd;
	};
	enum last_pt_type pt_type;
} last_pt_t;

last_pt_t get_last_pt(unsigned long addr);
void map_pdpte(pml4e_64 *ppml4e, unsigned long addr,
	       struct pt_permissions perms, virt_addr_map *paddr_map);
void map_pde(pdpte_64 *ppdpte, unsigned long addr, struct pt_permissions perms,
	     virt_addr_map *paddr_map);
void map_pte(pde_64 *ppde, unsigned long addr, struct pt_permissions perms,
	     virt_addr_map *paddr_map);
void fill_pte(pte_64 *ppte, unsigned long addr, struct pt_permissions perms,
	      virt_addr_map *paddr_map);

u64 find_free_pud(pud_t *ppud);
u64 find_free_pmd(pmd_t *ppmd);
u64 find_free_pte(pte_t *ppte);

void *map_physical(unsigned long addr, struct pt_permissions perms);
bool page_mapping_exist(unsigned long addr);