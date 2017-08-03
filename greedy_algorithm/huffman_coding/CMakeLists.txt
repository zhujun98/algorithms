cmake_minimum_required(VERSION 3.6)
project(huffman_coding)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Huffman.cpp)
add_executable(huffman_coding ${SOURCE_FILES})