#include "./../../core/chunk/chunk.h"
#include "./../../core/common/common.h"

uint8_t *disassembleInstAndGiveNextInstPtr(uint8_t *ptr);
bool checkIfDisassembleCompleted(uint8_t *curPtr, uint8_t *nextPtr);
void DisassembleChunk(Chunk *pChunk);
