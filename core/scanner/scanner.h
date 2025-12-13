#ifndef SCANNER_H
#define SCANNER_H

#include "./../../utils/files.h"
#include "./../common/common.h"
#include "./../tokens/token.h"

struct Scanner {
  long int TokenStartPos;
  long int TokenCurrPos;
  FILE *pTokenCurrent;
  int Line;
};
typedef struct Scanner Scanner;

void InitScanner(const char *pfilePath);
Token ScanToken();
void ResetScanner();

#endif // !SCANNER_H
