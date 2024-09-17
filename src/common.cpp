#include "common.hpp"
#include <array>
#include <cstdlib>
#include <memory>
#include <stdexcept>

std::string common::execCommand(const char *cmd) {
  std::array<char, 128> buffer;
  std::string result;

  // Open pipe to the command
  std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // Read output into result
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  system("clear");
  return result;
}
