
#include "system/apic.h"

bool check_apic()
{
    uint32_t eax, edx;
    cpuid(1, &eax, &edx);
    return edx & CPUID_FEAT_EDX_APIC;
}

void cpu_set_apic_base(uintptr_t apic)
{
    uint32_t edx = 0;
    uint32_t eax = (apic & 0xfffff0000) | IA32_APIC_BASE_MSR_ENABLE;

#ifdef __PHYSICAL_MEMORY_EXTENSION__
    edx = (apic >> 32) & 0x0f;
#endif

    cpuSetMSR(IA32_APIC_BASE_MSR, eax, edx);
}

uintptr_t cpu_get_apic_base()
{
    uint32_t eax, edx;
    cpuGetMSR(IA32_APIC_BASE_MSR, &eax, &edx);

#ifdef __PHYSICAL_MEMORY_EXTENSION__
    return (eax & 0xfffff000) | ((edx & 0x0f) << 32);
#else
    return (eax & 0xfffff000);
#endif
}

void enable_apic()
{
    /* Section 11.4.1 of 3rd volume of Intel SDM recommends mapping the base address page as strong uncacheable for correct APIC operation. */

    /* Hardware enable the Local APIC if it wasn't enabled */
    cpu_set_apic_base(cpu_get_apic_base());

    /* Set the Spurious Interrupt Vector Register bit 8 to start receiving interrupts */
    outb(0xF0, inb(0xF0) | 0x100);
}
