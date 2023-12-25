
#include "nstd/nstdmem.h"

void *memcpy(void *dstptr, const void *srcptr, size_t size)
{
	unsigned char *dst = (unsigned char *)dstptr;
	const unsigned char *src = (const unsigned char *)srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

int memcmp(const void *aptr, const void *bptr, size_t size)
{
	const unsigned char *a = (const unsigned char *)aptr;
	const unsigned char *b = (const unsigned char *)bptr;
	for (size_t i = 0; i < size; i++)
	{
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}

void *memmove(void *dstptr, const void *srcptr, size_t size)
{
	unsigned char *dst = (unsigned char *)dstptr;
	const unsigned char *src = (const unsigned char *)srcptr;
	if (dst < src)
	{
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	}
	else
	{
		for (size_t i = size; i != 0; i--)
			dst[i - 1] = src[i - 1];
	}
	return dstptr;
}

void *memset(void *bufptr, int value, size_t size)
{
	unsigned char *buf = (unsigned char *)bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char)value;
	return bufptr;
}

/* This should be computed at link time */
uint32_t free_mem_addr = 0x10000;
/* Implementation is just a pointer to some free memory which
 * keeps growing */
uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr)
{
	/* Pages are aligned to 4K, or 0x1000 */
	if (align == 1 && (free_mem_addr & 0xFFFFF000))
	{
		free_mem_addr &= 0xFFFFF000;
		free_mem_addr += 0x1000;
	}
	/* Save also the physical address */
	if (phys_addr)
		*phys_addr = free_mem_addr;

	uint32_t ret = free_mem_addr;
	free_mem_addr += size; /* Remember to increment the pointer */
	return ret;
}
