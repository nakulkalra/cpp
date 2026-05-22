#include "client_session.hpp"

#include "../protocol/parser.hpp"

#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

ClientSession::ClientSession(
    int client_fd,
    DataStore &store)
    : _client_fd(client_fd),
      _store(store) {}

void ClientSession::start()
{

    char buffer[1024];

    while (true)
    {

        std::memset(buffer, 0, sizeof(buffer));

        ssize_t bytes_received = recv(
            _client_fd,
            buffer,
            sizeof(buffer) - 1,
            0);

        if (bytes_received <= 0)
        {
            std::cout << "Client disconnected\n";
            break;
        }

        std::string input(buffer);

        while (!input.empty() &&
               (input.back() == '\n' ||
                input.back() == '\r'))
        {
            input.pop_back();
        }

        std::cout << "Received: "
                  << input
                  << '\n';

        Command command = Parser::parse(input);

        std::string response;

        switch (command.type)
        {

        case CommandType::PING:
        {
            response = "+PONG\r\n";
            break;
        }

        case CommandType::SET:
        {

            if (command.args.size() < 2)
            {
                response = "-ERR wrong number of arguments\r\n";
                break;
            }

            _store.set(
                command.args[0],
                command.args[1]);

            response = "+OK\r\n";
            break;
        }

        case CommandType::GET:
        {

            if (command.args.empty())
            {
                response = "-ERR wrong number of arguments\r\n";
                break;
            }

            auto value = _store.get(command.args[0]);

            if (value.has_value())
            {
                response =
                    "$" +
                    std::to_string(value->size()) +
                    "\r\n" +
                    *value +
                    "\r\n";
            }
            else
            {
                response = "$-1\r\n";
            }

            break;
        }

        case CommandType::DEL:
        {

            if (command.args.empty())
            {
                response = "-ERR wrong number of arguments\r\n";
                break;
            }

            bool deleted = _store.del(command.args[0]);

            response = deleted
                           ? ":1\r\n"
                           : ":0\r\n";

            break;
        }

        default:
        {
            response = "-ERR unknown command\r\n";
            break;
        }
        }

        send(
            _client_fd,
            response.c_str(),
            response.size(),
            0);
    }

    close(_client_fd);
}