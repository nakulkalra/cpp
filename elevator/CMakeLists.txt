cmake_minimum_required(VERSION 3.16)

project(elevator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(elevator
    src/main.cpp
)

target_include_directories(elevator PRIVATE src)