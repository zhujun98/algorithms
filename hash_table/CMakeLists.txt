cmake_minimum_required(VERSION 3.6)
project("Hash table")

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/assignments.h)
add_executable(hash_table ${SOURCE_FILES})