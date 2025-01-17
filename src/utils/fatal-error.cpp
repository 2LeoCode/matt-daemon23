#include <cstdio>
#include <cstdlib>

#include <print>
#include <string_view>

void fatalError(const std::string_view &message) {
  std::println(stderr, "Error: {}", message);
  std::exit(EXIT_FAILURE);
}
