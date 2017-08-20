project("graph")

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources
        src/main.cpp
        src/graph_utilities.h
        src/test/unittest_graph.h
        src/test/unittest_algorithms.h
        src/assignments.h
        src/ud_graph.cpp
        src/graph.cpp
        src/graph_algorithms/breath_first_search.h
        src/graph_algorithms/depth_first_search.h
        src/graph_algorithms/karger.h
        src/graph_algorithms/kosaraju.h
        src/graph_algorithms/dijkstra.h
        src/graph_algorithms/prim.h
        src/graph_algorithms/kruskal.h
        src/graph_algorithms/bellman_ford.h)

add_executable(run ${sources})