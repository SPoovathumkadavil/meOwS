/**
 * kernel.c
 *
 * This is the main file for the kernel.
 *
 * Make sure to read the README.md each each kernel archetecture directory
 * to understand how to build and run the kernel.
 *
 * This kernel is based on the tutorial at https://wiki.osdev.org/Bare_Bones
 */

#include "kernel.h"

#include "system/apic.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(COMPILING) && defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This os will only work for the 32-bit ix86 targets. */
#if defined(COMPILING) && !defined(__i386__)
#error "This os needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void)
{
	/* Initialize terminal interface */
	terminal_initialize();

	terminal_setcolor(VGA_COLOR_LIGHT_CYAN);

	terminal_writestring("Things \n");
	terminal_writestring("Yeah Things...\n");

	// Splash Screen
	terminal_printsplash();

	// Initialize the APIC
	printf("Initializing APIC...\n");

	if (check_apic())
	{
		printf("APIC is supported!\n");
		enable_apic();
		printf("APIC enabled!\n");
		printf("APIC base address: %x\n", cpu_get_apic_base());
	}
	else
	{
		printf("APIC is not supported!\n");
	}

	printf("Hello, kernel World!\n");
}
