/*
 * Interrupt Descriptor Tables
 */

#include "system/cpu/idt.h"

/*
 * idt_set_gate
 * Set an IDT gate
 */
void idt_set_gate(
    unsigned char num,
    unsigned long base,
    unsigned short sel,
    unsigned char flags)
{
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].zero = 0;
    idt[num].flags = flags | 0x60;
}

/*
 * idt_install
 * Install the IDTs
 */
void idt_install()
{
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uintptr_t)&idt;
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    idt_load();
}