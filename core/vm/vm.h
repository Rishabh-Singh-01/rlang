#ifndef VM_H
#define VM_H

#include "./../../utils/assertions.h"
#include "./../chunk/chunk.h"
#include "./../compiler/compiler.h"
#include "./../types/value/value.h"

#define VM_STACK_SIZE 256

enum OPCODE {
  OP_RETURN,
  OP_CONSTANT,
  OP_NEGATE,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE
};
typedef enum OPCODE OPCODE;

typedef struct {
  Chunk *Chunk;
  uint8_t *Ip;
  Value Stack[VM_STACK_SIZE];
  Value *stackTop;
} VM;

void InitVM();
void FreeVM();
INTERPRET_RESULT Interpret(const char *pfile);

#endif // !VM_H
