#include <unistd.h>

#include <exception>
#include <filesystem>
#include <print>

#include <errors.hpp>
#include <globals.hpp>
#include <logging.hpp>

namespace fs = std::filesystem;

void start() {
  auto logger = logging::FileLogger("matt-daemon", fs::path(logDirectory));

#ifndef DEVELOPMENT
  if (geteuid() != 0) {
    throw PermissionError();
  }
#endif

  std::println("Hello world!");
}

int main() {
  try {
    start();
  } catch (const PermissionError &e) {
    std::println(stderr, "Error: program must be run as root");
  } catch (const logging::FatalError &) {
    return 1;
  } catch (const std::exception &e) {
    std::println(stderr, "Uncaught error: {}", e.what());
    return 1;
  }
  return 0;
}
