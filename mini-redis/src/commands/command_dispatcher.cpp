#include "command_dispatcher.hpp"

#include "../protocol/resp_writer.hpp"

#include "del_handler.hpp"
#include "get_handler.hpp"
#include "ping_handler.hpp"
#include "set_handler.hpp"

CommandDispatcher::CommandDispatcher()
{

    _handlers[CommandType::PING] =
        std::make_unique<PingHandler>();

    _handlers[CommandType::SET] =
        std::make_unique<SetHandler>();

    _handlers[CommandType::GET] =
        std::make_unique<GetHandler>();

    _handlers[CommandType::DEL] =
        std::make_unique<DelHandler>();
}

std::string CommandDispatcher::dispatch(
    const Command &command,
    DataStore &store)
{

    auto it =
        _handlers.find(command.type);

    if (it == _handlers.end())
    {

        return RespWriter::error(
            "unknown command");
    }

    return it->second->execute(
        command,
        store);
}