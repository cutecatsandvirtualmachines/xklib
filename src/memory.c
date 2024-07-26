#include "memory.h"

bool page_mapping_exist(unsigned long addr, size_t size)
{
        pgd_t* pgd;
        pmd_t* pmd;
        pud_t* pud;
        pte_t* pte;
        struct mm_struct* mm = current->mm;
        unsigned long end_addr;
        pgd = pgd_offset(mm, addr);
        if (unlikely(!pgd) || unlikely(pgd_none(*pgd)) || unlikely(!pgd_present(*pgd)))
                return false;

        pud = pud_offset(pgd, addr);
        if (unlikely(!pud) || unlikely(pud_none(*pud)) || unlikely(!pud_present(*pud)))
                return false;

        pmd = pmd_offset(pud, addr);
        if (unlikely(!pmd) || unlikely(pmd_none(*pmd)) || unlikely(!pmd_present(*pmd)))
                return false;

        if (pmd_trans_huge(*pmd)) {
                end_addr = (((addr >> PMD_SHIFT) + 1) << PMD_SHIFT) - 1;
                goto end;
        }
        pte = pte_offset_kernel(pmd, addr);
        if (unlikely(!pte) || unlikely(!pte_present(*pte)))
                return false;
        end_addr = (((addr >> PAGE_SHIFT) + 1) << PAGE_SHIFT) - 1;
end:
        if (end_addr >= addr + size - 1)
                return true;
        return page_mapping_exist(end_addr + 1, size - (end_addr - addr + 1));
}