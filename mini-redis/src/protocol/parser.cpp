#include "parser.hpp"

#include <sstream>
#include <vector>

static CommandType getCommandType(
    const std::string &cmd)
{

    if (cmd == "PING")
    {
        return CommandType::PING;
    }

    if (cmd == "SET")
    {
        return CommandType::SET;
    }

    if (cmd == "GET")
    {
        return CommandType::GET;
    }

    if (cmd == "DEL")
    {
        return CommandType::DEL;
    }

    return CommandType::UNKNOWN;
}

std::optional<ParseResult> Parser::parse(
    const std::string &input)
{

    if (input.empty())
    {
        return std::nullopt;
    }

    // RESP only now
    if (input[0] == '*')
    {
        return parseRESP(input);
    }

    return std::nullopt;
}

std::optional<ParseResult> Parser::parseRESP(
    const std::string &input)
{

    size_t pos = 0;

    // Need "*"
    if (input[pos] != '*')
    {
        return std::nullopt;
    }

    pos++;

    // Find line end
    size_t line_end = input.find("\r\n", pos);

    if (line_end == std::string::npos)
    {
        return std::nullopt;
    }

    int count = std::stoi(
        input.substr(pos, line_end - pos));

    pos = line_end + 2;

    std::vector<std::string> parts;

    for (int i = 0; i < count; i++)
    {

        // Need enough bytes
        if (pos >= input.size())
        {
            return std::nullopt;
        }

        // Expect $
        if (input[pos] != '$')
        {
            return std::nullopt;
        }

        pos++;

        line_end = input.find("\r\n", pos);

        if (line_end == std::string::npos)
        {
            return std::nullopt;
        }

        int str_len = std::stoi(
            input.substr(pos, line_end - pos));

        pos = line_end + 2;

        // Check if full string exists
        if (pos + str_len + 2 > input.size())
        {
            return std::nullopt;
        }

        std::string value =
            input.substr(pos, str_len);

        parts.push_back(value);

        pos += str_len + 2;
    }

    Command command;

    if (parts.empty())
    {
        command.type = CommandType::UNKNOWN;
    }
    else
    {

        command.type =
            getCommandType(parts[0]);

        for (size_t i = 1;
             i < parts.size();
             i++)
        {

            command.args.push_back(parts[i]);
        }
    }

    return ParseResult{
        command,
        pos};
}