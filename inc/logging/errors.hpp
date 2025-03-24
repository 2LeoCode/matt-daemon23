#ifndef LOGGING_ERRORS_H
#define LOGGING_ERRORS_H

#include <exception>

namespace logging {

struct Error : public std::exception {};

struct FatalError : public Error {
  const char *what() const noexcept;
};

} // namespace logging

#endif
