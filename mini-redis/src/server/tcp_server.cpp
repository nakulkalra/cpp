#include "tcp_server.hpp"

#include "client_session.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

TcpServer::TcpServer(int port)
    : _port(port),
      _server_fd(-1) {}

void TcpServer::start()
{

    _server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (_server_fd < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(_port);

    if (bind(
            _server_fd,
            reinterpret_cast<sockaddr *>(&server_addr),
            sizeof(server_addr)) < 0)
    {

        close(_server_fd);
        throw std::runtime_error("Failed to bind socket");
    }

    if (listen(_server_fd, 5) < 0)
    {
        close(_server_fd);
        throw std::runtime_error("Failed to listen");
    }

    std::cout << "Server listening on port "
              << _port
              << '\n';

    while (true)
    {

        sockaddr_in client_addr{};
        socklen_t client_size = sizeof(client_addr);

        int client_fd = accept(
            _server_fd,
            reinterpret_cast<sockaddr *>(&client_addr),
            &client_size);

        if (client_fd < 0)
        {
            std::cerr << "Failed to accept client\n";
            continue;
        }

        std::cout << "Client connected\n";

        ClientSession session(
            client_fd,
            _store);

        session.start();
    }

    close(_server_fd);
}