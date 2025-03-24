#ifndef UTIL_H

#include <cassert>

#define Assume(expr, msg)                                                      \
  static_assert(expr, msg);                                                    \
  [[assume(expr)]];

#endif // !UTIL_H
