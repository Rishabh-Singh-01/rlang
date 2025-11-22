#include "value.h"
#include "./../../../utils/arraylist.h"
#include "./../../../utils/assertions.h"

void InitValueArray(ValueArray *pValueArray) {
  pValueArray->_capacity = 0;
  pValueArray->ByteCount = 0;
  pValueArray->Values = NULL;
}

void WriteValueArray(ValueArray *pValueArray, Value value) {
  ASSERT(pValueArray->_capacity <= pValueArray->ByteCount,
         "ValueArray capacity (%d) should not smaller than its byte count (%d)",
         pValueArray->_capacity, pValueArray->ByteCount);

  if (pValueArray->_capacity == pValueArray->ByteCount) {
    int updatedCapacity = GROW_CAPACITY(pValueArray->_capacity);
    pValueArray->Values = GROW_ARRAY(Value, pValueArray->Values,
                                     pValueArray->_capacity, updatedCapacity);
    pValueArray->_capacity = updatedCapacity;
  }

  pValueArray->Values[pValueArray->ByteCount] = value;
  pValueArray->ByteCount++;
}

void FreeValueArray(ValueArray *pValueArray) {
  FREE_ARRAY(pValueArray->Values);
  InitValueArray(pValueArray);
}
