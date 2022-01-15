cmake_minimum_required(VERSION 3.21)
project(CClientServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(CClient Client.h ClientMain.cpp)
add_executable(CServer Server.h ServerMain.cpp)

if(WIN32)
    target_link_libraries(CClient wsock32 ws2_32)
    target_link_libraries(CServer wsock32 ws2_32)
endif()
