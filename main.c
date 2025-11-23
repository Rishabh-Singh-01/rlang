#include "core/chunk/chunk.c"
#include "core/vm/vm.c"
#include "debug/disassembler/disassembler.c"

int main() {
  Chunk chunk;
  InitVM();
  InitChunk(&chunk);

  int constIdx = AddConstant(&chunk, 4);
  WriteChunk(&chunk, OP_CONSTANT, 6);
  WriteChunk(&chunk, constIdx, 6);

  constIdx = AddConstant(&chunk, 2);
  WriteChunk(&chunk, OP_CONSTANT, 6);
  WriteChunk(&chunk, constIdx, 6);

  WriteChunk(&chunk, OP_ADD, 6);

  constIdx = AddConstant(&chunk, 3);
  WriteChunk(&chunk, OP_CONSTANT, 6);
  WriteChunk(&chunk, constIdx, 6);

  WriteChunk(&chunk, OP_DIVIDE, 6);
  WriteChunk(&chunk, OP_NEGATE, 6);

  WriteChunk(&chunk, OP_RETURN, 6);

  DisassembleChunk(&chunk);
  Interpret(&chunk);
  printVMStack();

  FreeChunk(&chunk);
  FreeVM();

  return 0;
}
