#pragma once

#include "../db/datastore.hpp"

class TcpServer
{
public:
    explicit TcpServer(int port);

    void start();

private:
    int _port;
    int _server_fd;

    DataStore _store;
};