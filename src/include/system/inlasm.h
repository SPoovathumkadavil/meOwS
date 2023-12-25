
#if !defined(_INLASM_H_)
#define _INLASM_H_

#include <stdint.h>
#include <stdbool.h>

#define IRQ_OFF              \
    {                        \
        asm volatile("cli"); \
    }
#define IRQ_RES              \
    {                        \
        asm volatile("sti"); \
    }
#define PAUSE                \
    {                        \
        asm volatile("hlt"); \
    }
#define IRQS_ON_AND_PAUSE              \
    {                                  \
        asm volatile("sti\nhlt\ncli"); \
    }

static inline void __native_flush_tlb_single(unsigned long addr)
{
    asm volatile("invlpg (%0)" ::"r"(addr) : "memory");
}

/**
 * I know its fun, but don't run this
 */
static inline void __native_flush_tlb_global(void)
{
    unsigned long tmpreg;
    asm volatile("mov %%cr3, %0\n\t"
                 "mov %0, %%cr3"
                 : "=r"(tmpreg)
                 : /* no input */
                 : "memory");
}

/**
 * CPUID instruction
 */
static inline void cpuid(int code, uint32_t *a, uint32_t *d)
{
    asm volatile("cpuid"
                 : "=a"(*a), "=d"(*d)
                 : "0"(code)
                 : "ebx", "ecx");
}

static const uint32_t CPUID_FLAG_MSR = 1 << 5;

static inline bool cpuHasMSR()
{
    static uint32_t a, d; // eax, edx
    cpuid(1, &a, &d);
    return d & CPUID_FLAG_MSR;
}

static inline void cpuGetMSR(uint32_t msr, uint32_t *lo, uint32_t *hi)
{
    asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}

static inline void cpuSetMSR(uint32_t msr, uint32_t lo, uint32_t hi)
{
    asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}

/**
 * Read a 8/16/32-bit value at a given memory location using
 * another segment than the default C data segment.
 * Unfortunately there is no constraint for manipulating
 * segment registers directly, so issuing the mov <reg>,
 * <segmentreg> manually is required.
 */
static inline uint32_t farpeekl(uint16_t sel, void *off)
{
    uint32_t ret;
    asm("push %%fs\n\t"
        "mov  %1, %%fs\n\t"
        "mov  %%fs:(%2), %0\n\t"
        "pop  %%fs"
        : "=r"(ret) : "g"(sel), "r"(off));
    return ret;
}

/**
 * Write a 8/16/32-bit value to a segment:offset address too.
 * Note that much like in farpeek, this version of farpoke saves
 * and restore the segment register used for the access.
 */
static inline void farpokeb(uint16_t sel, void *off, uint8_t v)
{
    asm("push %%fs\n\t"
        "mov  %0, %%fs\n\t"
        "movb %2, %%fs:(%1)\n\t"
        "pop %%fs"
        : : "g"(sel), "r"(off), "r"(v));
    /* TODO: Should "memory" be in the clobber list here? */
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
    /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port)
                 : "memory");
    return ret;
}

/**
 * Wait a very small amount of time (1 to 4 microseconds, generally).
 * Useful for implementing a small delay for PIC remapping on
 * old hardware or generally as a simple but imprecise wait.

You can do an IO operation on any unused port: the Linux kernel by default uses port 0x80,
which is often used during POST to log information on the motherboard's
hex display but almost always unused after boot.
*/
static inline void io_wait(void)
{
    outb(0x80, 0);
}

/**
 * Returns a true boolean value if IRQs are enabled for the CPU.
 */
static inline bool are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile("pushf\n\t"
                 "pop %0"
                 : "=g"(flags));
    return flags & (1 << 9);
}

static inline unsigned long save_irqdisable(void)
{
    unsigned long flags;
    asm volatile("pushf\n\tcli\n\tpop %0" : "=r"(flags) : : "memory");
    return flags;
}

static inline void irqrestore(unsigned long flags)
{
    asm("push %0\n\tpopf" : : "rm"(flags) : "memory", "cc");
}

// Interrupts are disabled by setting the IF flag in the EFLAGS register to 0.
// static void intended_usage(void)
// {
//     unsigned long f = save_irqdisable();
//     do_whatever_without_irqs();
//     irqrestore(f);
// }

/**
 * Define a new interrupt table.
 */
static inline void lidt(void *base, uint16_t size)
{
    // This function works in 32 and 64bit mode
    struct
    {
        uint16_t length;
        void *base;
    } __attribute__((packed)) IDTR = {size, base};

    asm("lidt %0" : : "m"(IDTR)); // let the compiler choose an addressing mode
}

#endif // _INLASM_H_
