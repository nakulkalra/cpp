#pragma once

#include <string>
#include <vector>

enum class CommandType
{
    PING,
    SET,
    GET,
    DEL,
    UNKNOWN
};

struct Command
{
    CommandType type;
    std::vector<std::string> args;
};
