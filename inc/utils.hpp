#ifndef UTILS_H

#include <cassert>

#define Assume(expr)                                                           \
  assert(expr);                                                                \
  [[assume(expr)]];

#endif // !UTILS_H
