#include "vm.h"
#include "./../../utils/assertions.h"
#include <stdint.h>
#include <stdio.h>

VM vm;

void InitVM() {
  vm.Chunk = NULL;
  vm.Ip = NULL;
  vm.stackTop = &vm.Stack[0];
}

void FreeVM() { InitVM(); }

void printVMStack() {
  printf("----------------------------\n");
  printf("          VM Stack          \n");
  printf("----------------------------\n");
  Value *itr = vm.stackTop - 1;
  Value *pStackStart = vm.Stack;
  while (itr >= pStackStart) {
    printf("[");
    printf("%f", *itr);
    printf("]\n");
    itr--;
  }
}

void pushToVMStack(Value val) {
  *vm.stackTop = val;
  vm.stackTop++;
}
Value popVMStack() {
  Value val = *(vm.stackTop - 1);
  vm.stackTop--;
  return val;
}

INTERPRET_RESULT runVM() {
  while (true) {
    uint8_t opcode = *vm.Ip;

    switch (opcode) {
    case OP_RETURN:
      popVMStack();
      return INTERPRET_OK;
      break;
    case OP_CONSTANT: {
      vm.Ip++;
      uint8_t constIdx = *vm.Ip;
      Value constantVal = vm.Chunk->Constants.Values[constIdx];
      pushToVMStack(constantVal);
      break;
    }
    case OP_NEGATE: {
      Value val = popVMStack();
      pushToVMStack(-1 * val);
      break;
    }
    case OP_ADD: {
      Value secondVal = popVMStack();
      Value firstVal = popVMStack();
      pushToVMStack(firstVal + secondVal);
      break;
    }
    case OP_SUBTRACT: {
      Value secondVal = popVMStack();
      Value firstVal = popVMStack();
      pushToVMStack(firstVal - secondVal);
      break;
    }
    case OP_MULTIPLY: {
      Value secondVal = popVMStack();
      Value firstVal = popVMStack();
      pushToVMStack(firstVal * secondVal);
      break;
    }
    case OP_DIVIDE: {
      Value secondVal = popVMStack();
      Value firstVal = popVMStack();
      pushToVMStack(firstVal / secondVal);
      break;
    }
    default:
      ASSERT(false, "Non Detected Opcode (%hhu) for RunVM", opcode);
    }
    vm.Ip++;

    printVMStack();
  }
}

void Interpret(Chunk *pChunk) {
  vm.Chunk = pChunk;
  vm.Ip = vm.Chunk->Code;
  runVM();
}
