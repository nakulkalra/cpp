#pragma once

#include "../db/datastore.hpp"
#include "../protocol/command.hpp"

#include <string>

class CommandHandler
{
public:
    virtual ~CommandHandler() = default;

    virtual std::string execute(
        const Command &command,
        DataStore &store) = 0;
};