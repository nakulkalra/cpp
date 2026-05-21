#include <iostream>
#include "server/tcp_server.hpp"

int main()
{
    try
    {
        TcpServer server(6379);

        std::cout << "Mini Redis server starting on port 6379... \n";

        server.start();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Server error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}