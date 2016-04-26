cmake_minimum_required(VERSION 3.3)
project(Lab2)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(SOURCE_FILES
    Code2/hashTable.h
    Code2/Item.h
    Code2/main.cpp
    Code2/test.cpp)

add_executable(Lab2 ${SOURCE_FILES})