#include <asm/io.h>
#include <asm/page_64_types.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#include "debug.h"
#include "ia32.h"
#include "xstdint.h"

struct pml4t {
	pgd_t entry[512];
};

struct pdpt {
	pmd_t entry[512];
};

struct pdt {
	pud_t entry[512];
};

struct pt {
	pte_t entry[512];
};

enum last_pt_type { pt_type_invalid, pt_type_pte, pt_type_pmd };

typedef union _last_pt_t {
	struct {
		pte_t pte;
		pmd_t pmd;
	} value;
	enum last_pt_type pt_type;
} last_pt_t;

last_pt_t get_last_pt(unsigned long addr);
bool page_mapping_exist(unsigned long addr);