cmake_minimum_required(VERSION 3.6)
project(clustering)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/max_distance_clustering.cpp src/graph.cpp src/graph.h)
add_executable(clustering ${SOURCE_FILES})