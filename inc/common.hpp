#pragma once
#include <string>
#include <cstdint>
namespace common {
enum class ErrorCodes : uint8_t
{
    ERROR = 0,
    NORMAL,
    WARNING,
    NOT_DEFINED,
};
std::string execCommand(const char *cmd);
}
