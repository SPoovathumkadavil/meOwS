
#if !defined(_PIT_H_)
#define _PIT_H_

#include <system/inlasm.h>

/**
 * read the count of PIT channel 0
 */
unsigned read_pit_count(void);

/**
 * Set the reload value of PIT channel 0
 */
void set_pit_count(unsigned count);

#endif // _PIT_H_
