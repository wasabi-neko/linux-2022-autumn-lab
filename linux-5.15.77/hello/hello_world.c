// hello/hello_world.c
#include <linux/kernel.h>
#include <asm/syscalls.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/string.h>

inline unsigned long virt2phy_inline(struct mm_struct *mm, unsigned long vaddr)
{
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    struct page *page;
    unsigned long pfn;

    pgd = pgd_offset(mm, vaddr);
    if (pgd_none(*pgd)) {
        printk("not mapped in pgd\n");
        return -1;
    }

    p4d = p4d_offset(pgd, vaddr);
    if (p4d_none(*p4d)) {
        printk("not mapped in p4d\n");
        return -1;
    }

    pud = pud_offset(p4d, vaddr);
    if (pud_none(*pud)) {
        printk("not mapped in pud\n");
        return -1;
    }

    pmd = pmd_offset(pud, vaddr);
    if (pmd_none(*pmd)) {
        printk("not mapped in pmd\n");
        return -1;
    }

    pte = pte_offset_map(pmd, vaddr);
    if (pte_none(*pte)) {
        printk("not mapped in pte\n");
    }

    page = pte_page(*pte);
    pte_unmap(pte);

    pfn = page_to_pfn(page);
    printk("pfn: %lx\n", pfn);

    return (pfn & PAGE_MASK) | (vaddr & ~PAGE_MASK);
}

SYSCALL_DEFINE1(hello_world, int, a)
{
    printk("Hello World! %d\n", a);
    return 0;
}


SYSCALL_DEFINE3(my_virt_phy, unsigned long __user *, user_vaddrs, size_t , len_vaddr, unsigned long __user *, result)
{
    unsigned long *vaddr = kmalloc(sizeof(unsigned long) * len_vaddr, GFP_KERNEL);
    unsigned long *paddr = kmalloc(sizeof(unsigned long) * len_vaddr, GFP_KERNEL);
    copy_from_user(vaddr, user_vaddrs, sizeof(unsigned long) * len_vaddr);

    printk("test vaddr[0]: %lx", vaddr[0]);

    int i = 0;
    for (; i < len_vaddr; i++) {
        paddr[i] = virt2phy_inline(current->mm, vaddr[i]);
    }

    copy_to_user(result, paddr, len_vaddr* sizeof(unsigned long));

    return 0;
}