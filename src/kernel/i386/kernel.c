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
#include <nstd/nstdout.h>
#include <nstd/string.h>
#include <system/drivers/screen.h>
#include <system/cpu/isr.h>

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

	isr_install();
	irq_install();

	printf("Do Something > ");
}

void user_input(char *input)
{
	if (strcmp(input, "END") == 0)
	{
		kprint("Stopping the CPU. Bye!\n");
		asm volatile("hlt");
	}
	else if (strcmp(input, "PAGE") == 0)
	{
		/* Lesson 22: Code to test kmalloc, the rest is unchanged */
		uint32_t phys_addr;
		uint32_t page = kmalloc(1000, 1, &phys_addr);
		char page_str[16] = "";
		hex_to_ascii(page, page_str);
		char phys_str[16] = "";
		hex_to_ascii(phys_addr, phys_str);
		kprint("Page: ");
		kprint(page_str);
		kprint(", physical address: ");
		kprint(phys_str);
		kprint("\n");
	}
	kprint("You said: ");
	kprint(input);
	kprint("\n> ");
}
