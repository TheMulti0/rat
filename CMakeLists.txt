cmake_minimum_required(VERSION 3.21)
project(CClientServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(CClientServer main.cpp Client.h Server.h)

if(WIN32)
    target_link_libraries(CClientServer wsock32 ws2_32)
endif()
