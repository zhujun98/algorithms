project("graph")

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources
        src/main.cpp
        src/graph_utilities.h
        src/graph.h
        src/directed_graph.h
        src/undirected_graph.h
        src/graph_algorithms/breath_first_search.h
        src/graph_algorithms/depth_first_search.h
        src/graph_algorithms/dijkstra.h
        src/graph_algorithms/bellman_ford.h
        src/graph_algorithms/johnson.h
        src/graph_algorithms/floyd_warshall.h
        src/graph_algorithms/kosaraju.h
        src/graph_algorithms/prim.h
        src/graph_algorithms/kruskal.h
        src/graph_algorithms/karger.h
        src/test/unittest_graph.h
        src/test/test_dfs.h
        src/test/test_bfs.h
        src/test/test_dijkstra.h
        src/test/test_bellman_ford.h
        src/test/test_floyd_warshall.h
        src/test/test_johnson.h
        src/test/test_kosaraju.h
        src/test/test_prim.h
        src/test/test_kruskal.h
        src/test/test_karger.h
        src/assignments/assignment_shortest_path.h
        src/assignments/assignment_MST.h
        src/assignments/assignment_SCC.h
        src/assignments/assignment_karger.h
        src/assignments/assignment_all_pair_shortest_path.h)


add_executable(run ${sources})