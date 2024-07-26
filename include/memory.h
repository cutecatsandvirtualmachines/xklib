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

bool page_mapping_exist(unsigned long addr, size_t size);