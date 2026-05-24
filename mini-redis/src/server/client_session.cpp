#include "client_session.hpp"

#include "../protocol/parser.hpp"

#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "../protocol/resp_writer.hpp"

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

        std::cout << "Raw bytes:\n"
                  << buffer
                  << '\n';

        if (bytes_received <= 0)
        {
            std::cout << "Client disconnected\n";
            break;
        }

        _buffer.append(buffer, bytes_received);

        while (true)
        {

            auto result =
                Parser::parse(_buffer);

            if (!result.has_value())
            {
                break;
            }

            Command command =
                result->command;

            // Remove consumed bytes
            _buffer.erase(
                0,
                result->bytes_consumed);

            std::string response =
                _dispatcher.dispatch(
                    command,
                    _store);
            send(
                _client_fd,
                response.c_str(),
                response.size(),
                0);
        }
    }

    close(_client_fd);
}