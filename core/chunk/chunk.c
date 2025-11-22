#include "chunk.h"
#include "./../../core/common/common.h"
#include "./../../utils/arraylist.c"
#include "./../../utils/assertions.h"
#include <stdint.h>

void InitChunk(Chunk *pChunk) {
  pChunk->_capacity = 0;
  pChunk->byteCount = 0;
  pChunk->Code = NULL;
}

void WriteChunk(Chunk *pChunk, uint8_t byte) {
  ASSERT(pChunk->_capacity <= pChunk->byteCount,
         "Chunk capacity (%d) should not smaller than its byte count (%d)",
         pChunk->_capacity, pChunk->byteCount);

  if (pChunk->_capacity == pChunk->byteCount) {
    int updatedCapacity = GROW_CAPACITY(pChunk->_capacity);
    pChunk->Code =
        GROW_ARRAY(uint8_t, pChunk->Code, pChunk->_capacity, updatedCapacity);
    pChunk->_capacity = updatedCapacity;
  }

  pChunk->Code[pChunk->byteCount] = byte;
  pChunk->byteCount++;
}

void FreeChunk(Chunk *pChunk) {
  pChunk->_capacity = 0;
  pChunk->byteCount = 0;
  FREE_ARRAY(pChunk->Code);
  pChunk->Code = NULL;
}
