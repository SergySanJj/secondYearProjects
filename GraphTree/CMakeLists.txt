cmake_minimum_required(VERSION 3.12)
project(GraphTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(implementation)

add_executable(GraphTree src/main.cpp src/tests.cpp implementation/DateTime.cpp include/DateTime.h)

#include/Graph.h for some case save it here.