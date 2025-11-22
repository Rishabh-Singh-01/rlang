#include "core/chunk/chunk.c"
#include "core/vm/vm.c"
#include "debug/disassembler/disassembler.c"

int main() {
  Chunk chunk;
  InitChunk(&chunk);
  WriteChunk(&chunk, OP_RETURN);
  int constIdx = AddConstant(&chunk, 1.2);
  WriteChunk(&chunk, OP_CONSTANT);
  WriteChunk(&chunk, constIdx);
  DisassembleChunk(&chunk);
  FreeChunk(&chunk);

  return 0;
}
