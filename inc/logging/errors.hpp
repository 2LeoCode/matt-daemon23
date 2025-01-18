#ifndef LOGGING_ERRORS_H
#define LOGGING_ERRORS_H

#include <exception>

namespace logging {

struct FatalError : public std::exception {
  const char *what() const noexcept;
};

} // namespace logging

#endif
