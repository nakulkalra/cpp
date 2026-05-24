#pragma once

#include "command.hpp"

#include <optional>
#include <string>

struct ParseResult
{
    Command command;
    size_t bytes_consumed;
};

class Parser
{
public:
    static std::optional<ParseResult> parse(
        const std::string &input);

private:
    static std::optional<ParseResult> parseRESP(
        const std::string &input);
};