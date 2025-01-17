#include <cstdio>
#include <unistd.h>

#include <print>

#include "utils/utils.hpp"

int main() {
  if (geteuid() != 0) {
    fatalError("this program must be ran as root");
  }
  std::println("Hello world!");
  return 0;
}
