#pragma once

#include "command_handler.hpp"

class DelHandler : public CommandHandler
{
public:
    std::string execute(
        const Command &command,
        DataStore &store) override;
};