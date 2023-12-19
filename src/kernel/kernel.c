#include "terminal.h"
#include "kernel.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This os will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This os needs to be compiled with a ix86-elf compiler"
#endif
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	terminal_setcolor(VGA_COLOR_RED);

	terminal_writestring("Things \n");
	terminal_writestring("Yeah Things...\n");

  // Splash Screen
  terminal_writecenteredstring("                 ___            ____  \n");
  terminal_writecenteredstring(" _ __ ___   ___ / _ \\__      __/ ___| \n");
  terminal_writecenteredstring("| '_ ` _ \\ / _ \\ | | \\ \\ /\\ / /\\___ \\ \n");
  terminal_writecenteredstring(" | | | | | |  __/ |_| |\\ V  V /  ___) | \n");
  terminal_writecenteredstring("|_| |_| |_|\\___|\\___/  \\_/\\_/  |____/ \n");

}
