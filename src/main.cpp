#include <cstring>
#include <unistd.h>

#include <exception>
#include <filesystem>
#include <print>

#include <core.hpp>
#include <globals.hpp>
#include <logging.hpp>

namespace fs = std::filesystem;

void start() {
  auto logger = logging::FileLogger("matt-daemon", fs::path(logDirectory));

#ifndef DEVELOPMENT
  if (geteuid() != 0)
    throw core::PermissionError();

  auto cpid = fork();

  if (cpid == -1)
    throw core::StartupError(std::strerror(errno));

  if (cpid) {

    return;
  }
#endif

  logger.info("started successfully");
}

int main() {
  try {
    start();
  } catch (const core::Error &e) {
    std::println(stderr, "Error: {}\n", e.what());
    return 1;
  } catch (const logging::Error &e) {
    std::println(stderr, "Error: {}\n", e.what());
    return 1;
  } catch (const std::exception &e) {
    std::println(stderr, "Uncaught error: {}", e.what());
    return 1;
  }

  return 0;
}
