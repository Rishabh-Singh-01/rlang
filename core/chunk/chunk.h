#ifndef CHUNK_H
#define CHUNK_H

#include "./../common/common.h"

typedef struct {
  int _capacity;
  int byteCount;
  uint8_t *Code;
} Chunk;

void InitChunk(Chunk *pChunk);
void WriteChunk(Chunk *pChunk, uint8_t byte);
void FreeChunk(Chunk *pChunk);

#endif // !CHUNK_H
