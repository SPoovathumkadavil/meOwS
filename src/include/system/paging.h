
#if !defined(_PAGING_H_)
#define _PAGING_H_

#include <system/inlasm.h>

void *get_physaddr(void *virtualaddr);
void map_page(void *physaddr, void *virtualaddr, unsigned int flags);

#endif // _PAGING_H_
