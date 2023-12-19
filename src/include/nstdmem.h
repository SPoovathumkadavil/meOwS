
#ifndef _NSTDMEM_H_
#define _NSTDMEM_H_

#include <stddef.h>
#include <nstdmem.h>

int memcmp(const void *, const void *, size_t);
void *memcpy(void *__restrict, const void *__restrict, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
size_t strlen(const char *);

#endif // _NSTDMEM_H_
