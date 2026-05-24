#include "get_handler.hpp"

#include "../protocol/resp_writer.hpp"

std::string GetHandler::execute(
    const Command &command,
    DataStore &store)
{

    if (command.args.empty())
    {

        return RespWriter::error(
            "wrong number of arguments");
    }

    auto value =
        store.get(command.args[0]);

    if (!value.has_value())
    {

        return RespWriter::nullBulkString();
    }

    return RespWriter::bulkString(
        *value);
}