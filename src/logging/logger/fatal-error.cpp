#include <logging/logger.hpp>

namespace logging {

const char *FatalError::what() const noexcept { return "Logger: fatal error"; }

} // namespace logging
