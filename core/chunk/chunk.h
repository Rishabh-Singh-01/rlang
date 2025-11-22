#ifndef CHUNK_H
#define CHUNK_H

#include "./../common/common.h"
#include "./../types/value/value.h"

typedef struct {
  int _capacity;
  int ByteCount;
  uint8_t *Code;
  ValueArray Constants;
  int *LineInfo;
} Chunk;

void InitChunk(Chunk *pChunk);
void WriteChunk(Chunk *pChunk, uint8_t byte, int lineInfo);
void FreeChunk(Chunk *pChunk);
int AddConstant(Chunk *pChunk, Value constant);

#endif // !CHUNK_H
