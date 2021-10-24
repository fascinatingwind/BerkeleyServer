cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(src)

set(SOURCES
        "src/BerkeleyServer.cpp"
        "include/BerkeleyServer.h"
        src/main.cpp)

add_executable(BerkeleyServer ${SOURCES})

target_link_libraries(BerkeleyServer BerkeleyNetwork)