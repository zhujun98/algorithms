cmake_minimum_required(VERSION 3.8)
project(tsp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/tsp.h src/test_tsp.h)
add_executable(tsp ${SOURCE_FILES})