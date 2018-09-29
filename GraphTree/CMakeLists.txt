cmake_minimum_required(VERSION 3.12)
project(GraphTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(DateTime/include)
include_directories(DateTime/src)

include_directories(Graph/include)
include_directories(Graph/src)

add_executable(GraphTree src/main.cpp src/tests.cpp DateTime/src/DateTime.cpp DateTime/include/DateTime.h DateTime/include/DateTimeDelta.h DateTime/src/DateTimeDelta.cpp)

#include/Graph.h for some case save it here.