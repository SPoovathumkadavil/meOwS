
#ifndef _NSTDMEM_H_
#define _NSTDMEM_H_

#include <stddef.h>
#include <stdint.h>

int memcmp(const void *, const void *, size_t);
void *memcpy(void *__restrict, const void *__restrict, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);

/* At this stage there is no 'free' implemented. */
uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr);

#endif // _NSTDMEM_H_
