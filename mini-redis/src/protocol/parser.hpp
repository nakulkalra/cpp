#pragma once

#include "command.hpp"

class Parser
{
public:
    static Command parse(const std::string &input);
};