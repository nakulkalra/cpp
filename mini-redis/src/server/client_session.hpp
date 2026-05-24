#pragma once

#include "../db/datastore.hpp"
#include "../commands/command_dispatcher.hpp"

#include <string>

class ClientSession
{
public:
    ClientSession(
        int client_fd,
        DataStore &store);

    void start();

private:
    int _client_fd;

    DataStore &_store;

    std::string _buffer;
    CommandDispatcher _dispatcher;
};