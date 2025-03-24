#include <core/errors.hpp>
#include <format>

namespace core {

StartupError::StartupError(const std::string_view &reason)
    : m_msg(std::format("startup failed: {}", reason)) {}

const char *StartupError::what() const noexcept { return this->m_msg.data(); }

const char *PermissionError::what() const noexcept {
  return "this program requires root rights";
}

} // namespace core
