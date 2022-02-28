cmake_minimum_required(VERSION 3.21)
project(CClientServer)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SHARED shared/*.cpp shared/*.h)
add_library(Shared ${SHARED})

if(WIN32)
    target_link_libraries(Shared wsock32 ws2_32)
endif()

file(GLOB SERVER server/*.cpp server/*.h)
add_executable(server ${SERVER})
target_link_libraries(server Shared)

file(GLOB CLIENT client/*.cpp client/*.h)
add_executable(client ${CLIENT})
target_link_libraries(client Shared)