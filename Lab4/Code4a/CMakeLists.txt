cmake_minimum_required(VERSION 3.5)
project(Code4a)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    digraph.cpp
    digraph.h
    list.cpp
    list.h
    main.cpp
    queue.h)

add_executable(Code4a ${SOURCE_FILES})