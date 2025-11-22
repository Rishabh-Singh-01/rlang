#include "arraylist.h"
#include "assertions.h"

void *reallocate(void *ptr, size_t oldSize, size_t newSize) {
  ASSERT(oldSize <= newSize,
         "Reallocate should have new size (%zu) greater than old size (%zu)",
         newSize, oldSize);

  return realloc(ptr, newSize);
}
