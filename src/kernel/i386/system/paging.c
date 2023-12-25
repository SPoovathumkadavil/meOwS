
#include "system/paging.h"

void *get_physaddr(void *virtualaddr)
{
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;

    unsigned long *pd = (unsigned long *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.

    if (pd[pdindex] == 0)
    {
        // The PD entry is not present
        return 0;
    }

    unsigned long *pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.

    if (pt[ptindex] == 0)
    {
        // The PT entry is not present
        return 0;
    }

    return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtualaddr & 0xFFF));
}

void map_page(void *physaddr, void *virtualaddr, unsigned int flags)
{
    // Make sure that both addresses are page-aligned.

    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;

    unsigned long *pd = (unsigned long *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.
    // When it is not present, you need to create a new empty PT and
    // adjust the PDE accordingly.

    if (pd[pdindex] == 0)
    {
        // Allocate a new PT
        unsigned long *pt = (unsigned long *)0xFFC00000 + (0x400 * pdindex);
        // Clear it
        for (int i = 0; i < 1024; i++)
        {
            pt[i] = 0;
        }
        // Adjust the PDE
        pd[pdindex] = ((unsigned long)pt) | (flags & 0xFFF) | 0x01; // Present
    }

    unsigned long *pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.
    // When it is, then there is already a mapping present. What do you do now?

    if (pt[ptindex] != 0)
    {
        // The mapping is already present
        return;
    }

    pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01; // Present

    // Now you need to flush the entry in the TLB
    // or you might not notice the change.

    __native_flush_tlb_single((unsigned long)virtualaddr);
}
