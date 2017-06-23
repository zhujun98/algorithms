project("graph")

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources
        src/main.cpp
        src/graph_adj.cpp
        src/graph_adj.h
        src/graph_utilities.h
        src/graph_algorithms.h
        src/my_unit_test.h
        src/assignments.h)

add_executable(run ${sources})