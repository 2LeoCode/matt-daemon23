#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <locale>
#include <memory>
#include <string_view>

#include <logging/file-logger.hpp>

namespace fs = std::filesystem;
namespace chrono = std::chrono;

namespace logging {

FileLogger::FileLogger(const std::string_view &name, const fs::path &directory,
                       const std::locale &loc)
    : Logger(name, loc, nullptr) {
  auto now = chrono::system_clock::now();
  auto file = directory / std::vformat(loc, "{:L%Om-%EY}_{}.log",
                                       std::make_format_args(now, name));
  fs::create_directories(directory);
  this->m_stream = std::make_unique<std::ofstream>(file, std::ios::app);
}

fs::path FileLogger::filePath() const { return this->m_filePath; }

} // namespace logging
