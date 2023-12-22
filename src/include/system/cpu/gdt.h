

#if !defined(_GDT_H_)
#define _GDT_H_

#include <stdint.h>

/*
 * Global Descriptor Table Entry
 */
struct gdt_entry
{
    /* Limits */
    unsigned short limit_low;
    /* Segment address */
    unsigned short base_low;
    unsigned char base_middle;
    /* Access modes */
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

/*
 * GDT pointer
 */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[6];
struct gdt_ptr gp;

/**
 * (ASM) gdt_flush
 * Reloads the segment registers
 */
extern void gdt_flush();

/**
 * Set a GDT descriptor
 *
 * @param num The number for the descriptor to set.
 * @param base Base address
 * @param limit Limit
 * @param access Access permissions
 * @param gran Granularity
 */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

/*
 * gdt_install
 * Install the kernel's GDTs
 */
void gdt_install();

/**
 * Write a TSS (we only do this once)
 */
static void
write_tss(int32_t num, uint16_t ss0, uint32_t esp0);

/**
 * Set the kernel stack.
 *
 * @param stack Pointer to a the stack pointer for the kernel.
 */
void set_kernel_stack(uintptr_t stack);

#endif // _GDT_H_
