#ifndef LOGGING_LOGGER_H
#define LOGGING_LOGGER_H

#include <chrono>
#include <format>
#include <locale>
#include <memory>
#include <string>
#include <string_view>

#include <logging/errors.hpp>
#include <logging/log-level.hpp>

namespace chrono = std::chrono;

namespace logging {

class Logger {
public:
  Logger() = delete;
  Logger(const Logger &) = delete;
  Logger(Logger &&) = default;
  ~Logger() = default;

  Logger &operator=(const Logger &) = delete;
  Logger &operator=(Logger &&) = default;

  template <class... Args>
  void log(LogLevel level, std::format_string<Args...> fmt, Args... args) {
    auto now = chrono::floor<chrono::seconds>(chrono::system_clock::now());
    auto msg = std::format(fmt, args...);
    *this->m_stream << std::vformat(*this->m_loc,
                                    "{:L%Od/%Om/%EY-%OH:%OM:%OS} {} : {}\n",
                                    std::make_format_args(now, level, msg));
    if (level == LogLevel::Fatal)
      throw FatalError();
  }

  template <class... Args>
  void log(LogLevel level, std::wformat_string<Args...> fmt, Args... args) {
    auto now = chrono::floor<chrono::seconds>(chrono::system_clock::now());
    auto msg = std::format(fmt, args...);
    *this->m_stream << std::vformat(*this->m_loc,
                                    "{:L%Od/%Om/%EY-%OH:%OM:%OS} {} : {}\n",
                                    std::make_format_args(now, level, msg));
    if (level == LogLevel::Fatal)
      throw FatalError();
  }

  template <class... Args>
  void debug(std::format_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Debug, fmt, args...);
  }

  template <class... Args>
  void debug(std::wformat_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Debug, fmt, args...);
  }

  template <class... Args>
  void info(std::format_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Info, fmt, args...);
  }

  template <class... Args>
  void info(std::wformat_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Info, fmt, args...);
  }

  template <class... Args>
  void warning(std::format_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Warning, fmt, args...);
  }

  template <class... Args>
  void warning(std::wformat_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Warning, fmt, args...);
  }

  template <class... Args>
  void error(std::format_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Error, fmt, args...);
  }

  template <class... Args>
  void error(std::wformat_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Error, fmt, args...);
  }

  template <class... Args>
  [[noreturn]] void fatal(std::format_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Fatal, fmt, args...);
  }

  template <class... Args>
  [[noreturn]] void fatal(std::wformat_string<Args...> fmt, Args... args) {
    this->log(LogLevel::Fatal, fmt, args...);
  }

protected:
  Logger(const std::string_view &name, const std::locale &loc = std::locale(),
         std::unique_ptr<std::ostream> &&stream = nullptr);

  std::string m_name;
  std::unique_ptr<std::locale> m_loc;
  std::unique_ptr<std::ostream> m_stream;
};

} // namespace logging

#endif // !LOGGING_LOGGER_H
