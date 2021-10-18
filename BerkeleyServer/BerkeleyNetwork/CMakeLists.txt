# CMakeList.txt : CMake project for BerkeleyServer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

# Add source to this project's executable.
add_library(BerkeleyNetwork STATIC "BerkeleyNetwork.h" "BerkeleyNetwork.cpp")

# TODO: Add tests and install targets if needed.
