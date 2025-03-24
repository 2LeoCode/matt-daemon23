#ifndef CORE_ERRORS_H
#define CORE_ERRORS_H

#include <exception>
#include <string>
#include <string_view>

namespace core {

struct Error : public std::exception {};

struct StartupError : public Error {
  StartupError(const std::string_view &reason);

  const char *what() const noexcept;

private:
  std::string m_msg;
};

struct PermissionError : public Error {
  const char *what() const noexcept;
};

} // namespace core

#endif // !CORE_ERRORS_H
