#ifndef COMPILER_H
#define COMPILER_H

#include "./../../utils/files.h"
#include "./../common/common.h"
#include "./../scanner/scanner.h"

enum INTERPRET_RESULT {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
};

typedef enum INTERPRET_RESULT INTERPRET_RESULT;
INTERPRET_RESULT Compile(const char *pFilePath);

#endif // !COMPILER_H
