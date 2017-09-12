project("BST")

cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS "-g -Wall -pthread -std=c++11")

set(SOURCE_FILES
        src/main.cpp
        src/bst.h
        )
add_executable(bst ${SOURCE_FILES})