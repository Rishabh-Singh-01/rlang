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
    instLen++;
    break;
  case OP_CONSTANT:
    printf("OP_CONSTANT: %hhu\n", OP_CONSTANT);
    instLen++;
    uint8_t *pConstantVal = codePtr + instLen;
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
  int offset = 0;
  int totalBytesCount = pChunk->ByteCount;
  int curInstLen = 0;

  while (totalBytesCount > 0) {
    printf(">>>>>>>>>>>>>\n");

    curInstLen = disassembleInstAndGiveInstLen(pChunk, offset);
    totalBytesCount -= curInstLen;
    offset += curInstLen;

    printf("<<<<<<<<<<<<<\n");
  }
}
