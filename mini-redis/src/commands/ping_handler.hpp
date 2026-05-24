#pragma once

#include "command_handler.hpp"

class PingHandler : public CommandHandler
{
public:
    std::string execute(
        const Command &command,
        DataStore &store) override;
};