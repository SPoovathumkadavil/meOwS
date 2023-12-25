
#if !defined(_APIC_H_)
#define _APIC_H_

#include <system/inlasm.h>
#include <system/system.h>
#include <stdbool.h>

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100 // Processor is a BSP
#define IA32_APIC_BASE_MSR_ENABLE 0x800

/** returns a 'true' value if the CPU supports APIC
 *  and if the local APIC hasn't been disabled in MSRs
 *  note that this requires CPUID to be supported.
 */
bool check_apic();

/* Set the physical address for local APIC registers */
void cpu_set_apic_base(uintptr_t apic);

/**
 * Get the physical address of the APIC registers page
 * make sure you map it to virtual memory ;) (see paging.h)
 */
uintptr_t cpu_get_apic_base();

void enable_apic();

#endif // _APIC_H_
