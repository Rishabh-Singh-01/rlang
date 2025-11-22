#ifndef ASSERTIONS_H
#define ASSERTIONS_H

#include "./../core/common/common.h"

#define ASSERT(condn, msg, ...)                                                \
  do {                                                                         \
    if (!(condn)) {                                                            \
      printf(msg, __VA_ARGS__);                                                \
      abort();                                                                 \
    }                                                                          \
  } while (0);

#endif // !ASSERTIONS_H
