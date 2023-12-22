
#if !defined(_SYSTEM_H_)
#define _SYSTEM_H_

#include <stdint.h>
#include <system/inlasm.h>

#define STOP   \
    while (1)  \
    {          \
        PAUSE; \
    }

#define SYSCALL_VECTOR 0x7F
#define SIGNAL_RETURN 0xFFFFDEAF
#define THREAD_RETURN 0xFFFFB00F

typedef struct tss_entry
{
    uint32_t prev_tss;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} __attribute__((packed)) tss_entry_t;

extern void tss_flush();

/* Registers */
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

typedef void (*irq_handler_t)(struct regs *);

/* GDT */
extern void gdt_install();
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void set_kernel_stack(uintptr_t stack);

/* IDT */
extern void idt_install();
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

#endif // _SYSTEM_H_
