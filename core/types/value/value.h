#ifndef TYPES_VALUE_H
#define TYPES_VALUE_H

typedef double Value;

typedef struct {
  int _capacity;
  int ByteCount;
  Value *Values;
} ValueArray;

void InitValueArray(ValueArray *pValueArray);
void WriteValueArray(ValueArray *pValueArray, Value value);
void FreeValueArray(ValueArray *pValueArray);

#endif // !TYPES_VALUE_H
