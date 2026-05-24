#include "ping_handler.hpp"

#include "../protocol/resp_writer.hpp"

std::string PingHandler::execute(
    const Command &,
    DataStore &)
{
    return RespWriter::simpleString("PONG");
}