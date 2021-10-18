# CMakeList.txt : CMake project for BerkeleyServer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project("BerkeleyNetwork")

include_directories(include)
link_directories(src) 

set(SOURCES 
	"src/BerkeleyNetwork.cpp" 
	"include/BerkeleyNetwork.h"
)

# Add source to this project's executable.
add_library(BerkeleyNetwork STATIC ${SOURCES})

# TODO: Add tests and install targets if needed.
target_include_directories(BerkeleyNetwork PUBLIC  ${PROJECT_SOURCE_DIR}/include)
