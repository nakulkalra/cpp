#include "tcp_server.hpp"
#include <iostream>

TcpServer::TcpServer(int port) : _port(port) {}

void TcpServer::start()
{
    std::cout << "Server Listening on port " << _port << '\n';
}