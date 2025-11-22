#include "disassembler.h"
#include "./../../core/vm/vm.h"
#include "./../../utils/assertions.h"

uint8_t *disassembleInstAndGiveNextInstPtr(uint8_t *ptr) {
  uint8_t opcode = *ptr;
  uint8_t *nextInstPtr = ptr;
  switch (opcode) {
  case OP_RETURN:
    printf("OP_RETURN: %hhu", OP_RETURN);
    nextInstPtr++;
  default:
    ASSERT(false, "Invalid Disassemble Instruction state (%hhu)\n", opcode);
  }

  return nextInstPtr;
}

bool checkIfDisassembleCompleted(uint8_t *curPtr, uint8_t *nextPtr) {
  ASSERT(curPtr != NULL,
         "Cur Ptr should not be NULL during DisassembleChunk (%p)\n", curPtr);
  ASSERT(nextPtr != NULL,
         "Next Ptr should not be NULL during DisassembleChunk (%p)\n", nextPtr);

  return curPtr == nextPtr;
}

void DisassembleChunk(Chunk *pChunk) {
  printf("------ Chunk Info Start -------\n");
  uint8_t *ptr = pChunk->Code;
  uint8_t *nextInstPtr = ptr;
  bool isChunkDisassembled = false;

  while (!isChunkDisassembled) {
    printf("------ Instruction Start -------\n");
    nextInstPtr = disassembleInstAndGiveNextInstPtr(ptr);
    isChunkDisassembled = checkIfDisassembleCompleted(ptr, nextInstPtr);
    ptr = nextInstPtr;
    printf("------ Instruction End -------\n");
  }

  printf("------ Chunk Info End -------\n");
}
