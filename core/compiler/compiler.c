#include "compiler.h"

INTERPRET_RESULT Compile(const char *pfilePath) {
  InitScanner(pfilePath);

  INTERPRET_RESULT result = INTERPRET_COMPILE_ERROR;
  while (true) {
    // this loop will run till we encounter EOF or later some compiler error
    Token token = ScanToken();
    printf("---- New Token Found -----\n");
    printf("Token Type: %d\n", token.TokenType);
    printf("Token Line: %d\n", token.Line);
    printf("Token Length: %d\n", token.Length);
    printf("Token OffsetFromStart: %d\n", (int)token.OffsetFromStart);
    if (token.TokenType == TOKEN_EOF) {
      result = INTERPRET_OK;
      break;
    }
    if (token.TokenType == TOKEN_ERROR) {
      result = INTERPRET_COMPILE_ERROR;
      break;
    }
  }

  ResetScanner();
  return result;
}
