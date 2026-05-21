#include "tcp_server.hpp"
#include "../db/datastore.hpp"
#include "../protocol/parser.hpp"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

TcpServer::TcpServer(int port)
    : _port(port),
      _server_fd(-1) {}

void TcpServer::start()
{
    DataStore store;

    // Create socket
    _server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (_server_fd < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }

    // Configure address
    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(_port);

    // Bind
    if (bind(
            _server_fd,
            reinterpret_cast<sockaddr *>(&server_addr),
            sizeof(server_addr)) < 0)
    {

        close(_server_fd);
        throw std::runtime_error("Failed to bind socket");
    }

    // Listen
    if (listen(_server_fd, 5) < 0)
    {
        close(_server_fd);
        throw std::runtime_error("Failed to listen");
    }

    std::cout << "Server listening on port "
              << _port
              << '\n';

    // Accept one client
    sockaddr_in client_addr{};
    socklen_t client_size = sizeof(client_addr);

    int client_fd = accept(
        _server_fd,
        reinterpret_cast<sockaddr *>(&client_addr),
        &client_size);

    if (client_fd < 0)
    {
        close(_server_fd);
        throw std::runtime_error("Failed to accept client");
    }

    std::cout << "Client connected\n";

    char buffer[1024];

    while (true)
    {
        std::memset(buffer, 0, sizeof(buffer));

        ssize_t bytes_received = recv(
            client_fd,
            buffer,
            sizeof(buffer) - 1,
            0);

        if (bytes_received <= 0)
        {
            std::cout << "Client disconnected\n";
            break;
        }

        std::string input(buffer);

        // Remove trailing newline/carriage return
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

            store.set(
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

            auto value = store.get(command.args[0]);

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

            bool deleted = store.del(command.args[0]);

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
            client_fd,
            response.c_str(),
            response.size(),
            0);
    }
    close(client_fd);
    close(_server_fd);
}