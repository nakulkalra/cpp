#include "set_handler.hpp"

#include "../protocol/resp_writer.hpp"

std::string SetHandler::execute(
    const Command &command,
    DataStore &store)
{

    if (command.args.size() < 2)
    {

        return RespWriter::error(
            "wrong number of arguments");
    }

    store.set(
        command.args[0],
        command.args[1]);

    return RespWriter::simpleString("OK");
}