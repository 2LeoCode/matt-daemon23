#ifndef LOGGING_FILE_LOGGER_H
#define LOGGING_FILE_LOGGER_H

#include <filesystem>
#include <locale>
#include <string_view>

#include <logging/logger.hpp>

namespace fs = std::filesystem;

namespace logging {

class FileLogger : public Logger {
public:
  explicit FileLogger(const std::string_view &name, const fs::path &directory,
                      const std::locale &loc = std::locale());

  fs::path filePath() const;

private:
  fs::path m_filePath;
};

} // namespace logging

#endif // !LOGGING_FILE_LOGGER_H
