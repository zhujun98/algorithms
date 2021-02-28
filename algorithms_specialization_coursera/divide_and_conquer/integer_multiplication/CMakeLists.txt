project(karatsuba)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources
        src/main.cpp
        src/string_arithmetic.h
        src/unittest_string_arithmetic.h)

add_executable(karatsuba ${sources})