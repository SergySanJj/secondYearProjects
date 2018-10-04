cmake_minimum_required(VERSION 3.8)
project(GraphTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(DateTime/include)
include_directories(DateTime/src)

include_directories(Graph/include)
include_directories(Graph/src)

set(SOURCE_FILES src/main.cpp DateTime/src/DateTime.cpp DateTime/include/DateTime.h DateTime/include/DateTimeDelta.h DateTime/src/DateTimeDelta.cpp Graph/include/Graph.h)

add_executable(GraphTree ${SOURCE_FILES})

