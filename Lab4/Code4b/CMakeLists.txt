cmake_minimum_required(VERSION 3.5)
project(Code4b)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    dsets.cpp
    dsets.h
    edge.cpp
    edge.h
    graph.cpp
    graph.h
    heap.h
    list.cpp
    list.h
    main.cpp)

add_executable(Code4b ${SOURCE_FILES})