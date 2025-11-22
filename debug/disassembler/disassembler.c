#include "disassembler.h"
#include "./../../core/vm/vm.h"
#include "./../../utils/assertions.h"
#include <stdint.h>

int disassembleInstAndGiveInstLen(Chunk *pChunk, uint8_t *ptr) {
  uint8_t opcode = *ptr;
  int instLen = 0;

  switch (opcode) {
  case OP_RETURN:
    printf("OP_RETURN: %hhu\n", OP_RETURN);
    instLen++;
    break;
  case OP_CONSTANT:
    printf("OP_CONSTANT: %hhu\n", OP_CONSTANT);
    instLen++;
    uint8_t *pConstantVal = ptr + instLen;
    uint8_t constantValIdx = *pConstantVal;
    Value constantVal = pChunk->Constants.Values[constantValIdx];
    printf("Corresponding Constant Value: %f\n", constantVal);
    instLen++;
    break;
  default:
    ASSERT(false, "Invalid Disassemble Instruction state (%hhu)\n", opcode);
  }

  return instLen;
}

void DisassembleChunk(Chunk *pChunk) {
  uint8_t *ptr = pChunk->Code;
  int totalBytesCount = pChunk->ByteCount;
  int curInstLen = 0;

  while (totalBytesCount > 0) {
    printf(">>>>>>>>>>>>>\n");

    curInstLen = disassembleInstAndGiveInstLen(pChunk, ptr);
    totalBytesCount -= curInstLen;
    ptr += curInstLen;

    printf("<<<<<<<<<<<<<\n");
  }
}
