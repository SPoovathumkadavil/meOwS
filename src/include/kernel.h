
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <system/terminal.h>

nstd::terminal term;

#ifdef __cplusplus
extern "C" /* Use C linkage for kernel_main. */
{
#endif

	// The kernel's main function.
	void kernel_main();

#ifdef __cplusplus
}
#endif

#endif // !_KERNEL_H_
