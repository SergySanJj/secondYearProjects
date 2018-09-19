cmake_minimum_required(VERSION 3.12)
project(GraphTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(GraphTree src/main.cpp include/Graph.h include/Tree.h)