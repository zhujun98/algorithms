cmake_minimum_required(VERSION 3.6)
project(knapsack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/knapsack.cpp)
add_executable(knapsack ${SOURCE_FILES})