#include "del_handler.hpp"

#include "../protocol/resp_writer.hpp"

std::string DelHandler::execute(
    const Command &command,
    DataStore &store)
{

    if (command.args.empty())
    {

        return RespWriter::error(
            "wrong number of arguments");
    }

    bool deleted =
        store.del(command.args[0]);

    return RespWriter::integer(
        deleted ? 1 : 0);
}