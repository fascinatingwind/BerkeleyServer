cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project("BerkeleyNetwork")

include_directories(include)
link_directories(src)

set(SOURCES
        "src/Socket.cpp"
        "include/Socket.h"
        "src/TCPSocket.cpp"
        "include/TCPSocket.h"
        "src/UDPSocket.cpp"
        "include/UDPSocket.h"
        "include/Connection.h"
        "src/Connection.cpp"
        "include/TCPConnection.h"
        "src/TCPConnection.cpp"
        "src/UDPConnection.cpp"
        "include/UDPConnection.h"
        "src/NetworkHelper.cpp"
        "include/NetworkHelper.h"
        "src/EventManager.cpp"
        "include/EventManager.h"
        src/SockBase.cpp include/SockBase.h)

add_library(BerkeleyNetwork STATIC ${SOURCES})

target_include_directories(BerkeleyNetwork PUBLIC ${PROJECT_SOURCE_DIR}/include)
