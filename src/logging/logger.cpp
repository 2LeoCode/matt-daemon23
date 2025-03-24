#include <locale>
#include <memory>
#include <ostream>
#include <string_view>
#include <utility>

#include <logging/logger.hpp>

namespace logging {

Logger::Logger(const std::string_view &name, const std::locale &loc,
               std::ostream *&&stream)
    : m_name(name), m_loc(new std::locale(loc)), m_stream(std::move(stream)) {}

Logger::Logger(const std::string_view &name, const std::locale &loc,
               std::unique_ptr<std::ostream> &&stream)
    : m_name(name), m_loc(new std::locale(loc)), m_stream(std::move(stream)) {}

} // namespace logging
