#ifndef LOGGING_LOG_LEVEL_H
#define LOGGING_LOG_LEVEL_H

#include <format>
#include <string>

namespace logging {

enum class LogLevel { Debug, Info, Warning, Error, Fatal };

}

namespace std {

constexpr const char *to_string(logging::LogLevel level) {
  using enum logging::LogLevel;

  switch (level) {
  case Debug:
    return "DEBUG";
  case Info:
    return "INFO";
  case Warning:
    return "WARNING";
  case Error:
    return "ERROR";
  case Fatal:
    return "FATAL";
  }
}

template <> struct formatter<logging::LogLevel> : formatter<string> {
  template <class FormatContext>
  auto format(logging::LogLevel level, FormatContext &ctx) const {
    return formatter<string>::format(std::to_string(level), ctx);
  }
};

} // namespace std

#endif // !LOGGING_LOG_LEVEL_H
