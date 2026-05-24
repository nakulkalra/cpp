#pragma once

#include "../db/datastore.hpp"
#include "../protocol/command.hpp"

#include "command_handler.hpp"

#include <memory>
#include <unordered_map>

class CommandDispatcher
{
public:
    CommandDispatcher();

    std::string dispatch(
        const Command &command,
        DataStore &store);

private:
    std::unordered_map<
        CommandType,
        std::unique_ptr<CommandHandler>>
        _handlers;
};