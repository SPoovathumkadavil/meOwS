
#if !defined(_IDT_H_)
#define _IDT_H_

#include <stdint.h>
#include <nstd/nstdmem.h>

/*
 * IDT Entry
 */
struct idt_entry
{
    unsigned short base_low;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));

/*
 * IDT pointer
 */
struct idt_ptr
{
    unsigned short limit;
    uintptr_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load();

/*
 * idt_set_gate
 * Set an IDT gate
 */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

/*
 * idt_install
 * Install the IDTs
 */
void idt_install();

#endif // _IDT_H_
