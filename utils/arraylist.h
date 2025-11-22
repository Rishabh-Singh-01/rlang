#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "./../core/common/common.h"

#define GROW_CAPACITY(capacity) (capacity < 8 ? 8 : capacity * 2)
#define GROW_ARRAY(type, ptr, oldCount, newCount)                              \
  ((type *)reallocate((void *)ptr, sizeof(type) * oldCount,                    \
                      sizeof(type) * newCount))
#define FREE_ARRAY(ptr) free(ptr)

void *reallocate(void *ptr, size_t oldSize, size_t newSize);

#endif // !ARRAYLIST_H
