cmake_minimum_required(VERSION 3.12)
project(GraphTree)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

include_directories(DateTime/include)
include_directories(DateTime/src)

include_directories(Graph/include)
include_directories(Graph/src)

set(SOURCE_FILES src/main.cpp DateTime/src/DateTime.cpp DateTime/include/DateTime.h DateTime/include/DateTimeDelta.h DateTime/src/DateTimeDelta.cpp Graph/include/Graph.h dependencies/random.hpp Tests/tests.cpp)

add_executable(GraphTree ${SOURCE_FILES})

target_link_libraries(GraphTree gtest gtest_main)

