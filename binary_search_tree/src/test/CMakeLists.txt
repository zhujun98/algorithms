project("BST")

cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS "-g -Wall -pthread -std=c++11")

set(SOURCE_FILES ../bst.h
                 test_bst.cpp)

add_executable(bst_test ${SOURCE_FILES})