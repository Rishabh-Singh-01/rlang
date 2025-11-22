#include "chunk.h"
#include "./../../core/common/common.h"
#include "./../../utils/arraylist.c"
#include "./../../utils/assertions.h"
#include "./../types/value/value.c"

void InitChunk(Chunk *pChunk) {
  pChunk->_capacity = 0;
  pChunk->ByteCount = 0;
  pChunk->Code = NULL;
  pChunk->LineInfo = NULL;
  InitValueArray(&(pChunk->Constants));
}

void WriteChunk(Chunk *pChunk, uint8_t byte, int lineInfo) {
  ASSERT(pChunk->_capacity >= pChunk->ByteCount,
         "Chunk capacity (%d) should be greater than its byte count (%d)",
         pChunk->_capacity, pChunk->ByteCount);
  ASSERT(lineInfo >= 0, "Line Info (%d) for Chunk should be greater than 0",
         lineInfo);

  if (pChunk->_capacity == pChunk->ByteCount) {
    int updatedCapacity = GROW_CAPACITY(pChunk->_capacity);
    pChunk->Code =
        GROW_ARRAY(uint8_t, pChunk->Code, pChunk->_capacity, updatedCapacity);
    pChunk->LineInfo =
        GROW_ARRAY(int, pChunk->LineInfo, pChunk->_capacity, updatedCapacity);
    pChunk->_capacity = updatedCapacity;
  }

  pChunk->Code[pChunk->ByteCount] = byte;
  pChunk->LineInfo[pChunk->ByteCount] = lineInfo;
  pChunk->ByteCount++;
}

void FreeChunk(Chunk *pChunk) {
  FREE_ARRAY(pChunk->Code);
  FREE_ARRAY(pChunk->LineInfo);
  FreeValueArray(&(pChunk->Constants));
  InitChunk(pChunk);
}

int AddConstant(Chunk *pChunk, Value constant) {
  WriteValueArray(&(pChunk->Constants), constant);
  return pChunk->Constants.ByteCount - 1;
}
