
#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <nstd/nstdout.h>

typedef enum
{
    INFO = 0, /* Unimportant */
    NOTICE,   /* Important, but not bad */
    WARNING,  /* Not what was expected, but still okay */
    ERROR,    /* This is bad... */
    CRITICAL  /* Shit */
} log_type_t;

log_type_t debug_level;
void _debug_print(char *title, int line_no, log_type_t level, char *fmt, ...);

#ifndef MODULE_NAME
#define MODULE_NAME __FILE__
#endif

#ifndef QUIET
#define debug_print(level, ...) _debug_print(MODULE_NAME, __LINE__, level, __VA_ARGS__)
#else
#define debug_print(level, ...)
#endif

#endif