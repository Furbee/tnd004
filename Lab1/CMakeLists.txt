cmake_minimum_required(VERSION 3.3)
project(Lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Code1/main.cpp Code1/set.cpp Code1/set.h Code1/Node.cpp Code1/Node.h)

add_executable(Lab1 ${SOURCE_FILES})