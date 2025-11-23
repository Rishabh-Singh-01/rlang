#ifndef VM_H
#define VM_H

#include "./../chunk/chunk.h"
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

enum INTERPRET_RESULT {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
};
typedef enum INTERPRET_RESULT INTERPRET_RESULT;

typedef struct {
  Chunk *Chunk;
  uint8_t *Ip;
  Value Stack[VM_STACK_SIZE];
  Value *stackTop;
} VM;

void InitVM();
void FreeVM();
void Interpret(Chunk *pChunk);

#endif // !VM_H
