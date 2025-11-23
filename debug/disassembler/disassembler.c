#include "disassembler.h"
#include "./../../core/vm/vm.h"
#include "./../../utils/assertions.h"
#include <stdint.h>
#include <stdio.h>

int disassembleInstAndGiveInstLen(Chunk *pChunk, int offset) {
  uint8_t *codePtr = pChunk->Code + offset;
  uint8_t opcode = *codePtr;
  int instLen = 0;
  printf("Line Number: %d\n", pChunk->LineInfo[offset]);

  switch (opcode) {
  case OP_RETURN:
    printf("OP_RETURN: %hhu\n", OP_RETURN);
    break;
  case OP_CONSTANT:
    printf("OP_CONSTANT: %hhu\n", OP_CONSTANT);
    uint8_t *pConstantVal = codePtr + 1;
    uint8_t constantValIdx = *pConstantVal;
    Value constantVal = pChunk->Constants.Values[constantValIdx];
    printf("Constant Value: %f\n", constantVal);
    instLen++;
    break;
  case OP_NEGATE: {
    printf("OP_NEGATE: %hhu\n", OP_NEGATE);
    break;
  }
  case OP_ADD: {
    printf("OP_ADD: %hhu\n", OP_ADD);
    break;
  }
  case OP_SUBTRACT: {
    printf("OP_SUBTRACT: %hhu\n", OP_SUBTRACT);
    break;
  }
  case OP_MULTIPLY: {
    printf("OP_MULTIPLY: %hhu\n", OP_MULTIPLY);
    break;
  }
  case OP_DIVIDE: {
    printf("OP_DIVIDE: %hhu\n", OP_DIVIDE);
    break;
  }
  default:
    ASSERT(false, "Invalid Disassemble Instruction state (%hhu)\n", opcode);
  }

  instLen++;
  return instLen;
}

void DisassembleChunk(Chunk *pChunk) {
  int offset = 0;
  int totalBytesCount = pChunk->ByteCount;
  int curInstLen = 0;

  while (totalBytesCount > 0) {
    printf("-----------------------------\n");
    printf("          Inst Byte          \n");
    printf("-----------------------------\n");
    curInstLen = disassembleInstAndGiveInstLen(pChunk, offset);
    totalBytesCount -= curInstLen;
    offset += curInstLen;
  }
}
