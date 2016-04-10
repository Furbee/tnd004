cmake_minimum_required(VERSION 3.3)
project(Single_Linked_List)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Node.cpp Node.h set.cpp set.h)
add_executable(Single_Linked_List ${SOURCE_FILES})