# CMakeList.txt : CMake project for BerkeleyServer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project("BerkeleyClient")

include_directories(include)
link_directories(src) 

set(SOURCES 
	"src/BerkeleyClient.cpp" 
	"include/BerkeleyClient.h"
)

# Add source to this project's executable.
add_executable (BerkeleyClient ${SOURCES})

# TODO: Add tests and install targets if needed.
target_link_libraries(BerkeleyClient BerkeleyNetwork)