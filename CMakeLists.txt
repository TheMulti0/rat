cmake_minimum_required(VERSION 3.21)
project(CClientServer)

set(CMAKE_CXX_STANDARD 14)

file(GLOB LIB_SOURCES *.cpp)
file(GLOB LIB_HEADERS *.h)
add_executable(CClientServer ${LIB_SOURCES} ${LIB_HEADERS})

if(WIN32)
    target_link_libraries(CClientServer wsock32 ws2_32)
endif()

#add_executable(CClient ClientMain.cpp)
#target_link_libraries(CClient CClientServer)

#add_executable(CServer ServerMain.cpp)
#target_link_libraries(CServer CClientServer)