#include "parser.hpp"

#include <sstream>

Command Parser::parse(const std::string &input)
{
    std::stringstream ss(input);

    std::string word;
    ss >> word;

    Command command;

    if (word == "PING")
    {
        command.type = CommandType::PING;
    }
    else if (word == "SET")
    {
        command.type = CommandType::SET;
    }
    else if (word == "GET")
    {
        command.type = CommandType::GET;
    }
    else if (word == "DEL")
    {
        command.type = CommandType::DEL;
    }
    else
    {
        command.type = CommandType::UNKNOWN;
    }

    while (ss >> word)
    {
        command.args.push_back(word);
    }

    return command;
}