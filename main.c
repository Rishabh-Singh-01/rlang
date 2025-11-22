#include "core/chunk/chunk.c"
#include "core/vm/vm.c"
#include "debug/disassembler/disassembler.c"

int main() {
  Chunk chunk;
  InitChunk(&chunk);
  WriteChunk(&chunk, OP_RETURN);
  DisassembleChunk(&chunk);
  FreeChunk(&chunk);

  return 0;
}
