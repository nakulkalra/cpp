#include "resp_writer.hpp"

std::string RespWriter::simpleString(
    const std::string &value)
{
    return "+" + value + "\r\n";
}

std::string RespWriter::error(
    const std::string &value)
{
    return "-ERR " + value + "\r\n";
}

std::string RespWriter::bulkString(
    const std::string &value)
{
    return "$" +
           std::to_string(value.size()) +
           "\r\n" +
           value +
           "\r\n";
}

std::string RespWriter::nullBulkString()
{
    return "$-1\r\n";
}

std::string RespWriter::integer(
    int value)
{
    return ":" +
           std::to_string(value) +
           "\r\n";
}