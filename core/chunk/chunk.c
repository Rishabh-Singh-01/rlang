#include "chunk.h"
#include "./../../core/common/common.h"
#include "./../../utils/arraylist.c"
#include "./../../utils/assertions.h"
#include "./../types/value/value.c"

void InitChunk(Chunk *pChunk) {
  pChunk->_capacity = 0;
  pChunk->ByteCount = 0;
  pChunk->Code = NULL;
  InitValueArray(&(pChunk->Constants));
}

void WriteChunk(Chunk *pChunk, uint8_t byte) {
  ASSERT(pChunk->_capacity >= pChunk->ByteCount,
         "Chunk capacity (%d) should be greater than its byte count (%d)",
         pChunk->_capacity, pChunk->ByteCount);

  if (pChunk->_capacity == pChunk->ByteCount) {
    int updatedCapacity = GROW_CAPACITY(pChunk->_capacity);
    pChunk->Code =
        GROW_ARRAY(uint8_t, pChunk->Code, pChunk->_capacity, updatedCapacity);
    pChunk->_capacity = updatedCapacity;
  }

  pChunk->Code[pChunk->ByteCount] = byte;
  pChunk->ByteCount++;
}

void FreeChunk(Chunk *pChunk) {
  FREE_ARRAY(pChunk->Code);
  FreeValueArray(&(pChunk->Constants));
  InitChunk(pChunk);
}

int AddConstant(Chunk *pChunk, Value constant) {
  WriteValueArray(&(pChunk->Constants), constant);
  return pChunk->Constants.ByteCount - 1;
}
