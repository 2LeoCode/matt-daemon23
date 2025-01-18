#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <chrono>
#include <format>
#include <locale>
#include <memory>
#include <string>
#include <string_view>

#include "errors.hpp"

namespace chrono = std::chrono;

namespace logging {

class Logger {
public:
  enum class Level { Info, Warning, Error, Fatal };

  Logger(const Logger &other) = delete;
  Logger(Logger &&other) = delete;

  Logger &operator=(const Logger &other) = delete;
  Logger &operator=(Logger &&other) = delete;

  template <class... Args>
  void log(Level level, std::format_string<Args...> fmt, Args... args) {
    *this->m_stream << format(
        this->m_loc, "{:L%Od/%Om/%EY-%OH-%OM-%OS} {}: {}\n",
        chrono::system_clock::now(), level, std::format(fmt, args...));
    if (level == Level::Fatal)
      throw FatalError();
  }

  template <class... Args>
  void log(Level level, std::wformat_string<Args...> fmt, Args... args) {
    *this->m_stream << format(this->m_loc, "{:L%Od/%Om/%EY-%OH-%OM-%OS} {}: {}",
                              chrono::system_clock::now(), level,
                              std::format(fmt, args...));
    if (level == Level::Fatal)
      throw FatalError();
  }

  template <class... Args>
  void info(std::format_string<Args...> fmt, Args... args) {
    this->log(Level::Info, fmt, args...);
  }

  template <class... Args>
  void info(std::wformat_string<Args...> fmt, Args... args) {
    this->log(Level::Info, fmt, args...);
  }

  template <class... Args>
  void warning(std::format_string<Args...> fmt, Args... args) {
    this->log(Level::Warning, fmt, args...);
  }

  template <class... Args>
  void warning(std::wformat_string<Args...> fmt, Args... args) {
    this->log(Level::Warning, fmt, args...);
  }

  template <class... Args>
  void error(std::format_string<Args...> fmt, Args... args) {
    this->log(Level::Error, fmt, args...);
  }

  template <class... Args>
  void error(std::wformat_string<Args...> fmt, Args... args) {
    this->log(Level::Error, fmt, args...);
  }

  template <class... Args>
  [[noreturn]] void fatal(std::format_string<Args...> fmt, Args... args) {
    this->log(Level::Fatal, fmt, args...);
  }

  template <class... Args>
  [[noreturn]] void fatal(std::wformat_string<Args...> fmt, Args... args) {
    this->log(Level::Fatal, fmt, args...);
  }

protected:
  Logger(const std::string_view &name, const std::locale &loc = std::locale(),
         std::ostream *&&stream = nullptr);
  Logger(const std::string_view &name, const std::locale &loc = std::locale(),
         std::unique_ptr<std::ostream> &&stream = nullptr);

  const std::string m_name;
  const std::locale m_loc;
  std::unique_ptr<std::ostream> m_stream;
};

} // namespace logging

template <> struct std::formatter<logging::Logger::Level> : formatter<string> {
  auto format(logging::Logger::Level level, format_context &ctx) const {
    const char *levelStr;

    switch (level) {
    case logging::Logger::Level::Info:
      levelStr = "INFO";
      break;
    case logging::Logger::Level::Warning:
      levelStr = "WARNING";
      break;
    case logging::Logger::Level::Error:
      levelStr = "ERROR";
      break;
    case logging::Logger::Level::Fatal:
      levelStr = "FATAL";
      break;
    }
    return formatter<string>::format(levelStr, ctx);
  }
};

#endif // !LOGGING_LOGGER_H
