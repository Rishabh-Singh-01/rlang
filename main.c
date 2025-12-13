#include "./utils/files.c"
#include "core/chunk/chunk.c"
#include "core/compiler/compiler.c"
#include "core/scanner/scanner.c"
#include "core/vm/vm.c"
#include "debug/disassembler/disassembler.c"

int main() {
  InitVM();

  // TODO: only supporting read file (no REPL); do it later
  //

  // directly pass the stuff in Interpret
  // interpret will complile the frontend to tokens (no need to load it ever)
  INTERPRET_RESULT result = Interpret("./assets/classes.clox");
  printf("Found the interpret result as %d", result);
  //

  FreeVM();
  return 0;
}
