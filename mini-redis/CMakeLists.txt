cmake_minimum_required(VERSION 3.16)

project(mini_redis)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mini_redis
    src/main.cpp

    src/server/tcp_server.cpp
    src/server/client_session.cpp

    src/db/datastore.cpp

    src/protocol/parser.cpp
    src/protocol/command.cpp

    src/protocol/resp_writer.cpp
)

target_include_directories(mini_redis PRIVATE src)