
#include "system/nstdlib.h"

__attribute__((__noreturn__)) void abort(void)
{
#if defined(__is_libk)
	// TODO: Add proper kernel panic.
	printf_("kernel: panic: abort()\n");
#else
	// TODO: Abnormally terminate the process as if by SIGABRT.
	printf_("abort()\n");
#endif
	while (1)
	{
	}
	__builtin_unreachable();
}
