cmake_minimum_required(VERSION 3.3)
project(spz1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Allocator.cpp Allocator.h ListOfBlock.cpp ListOfBlock.h)
add_executable(spz1 ${SOURCE_FILES})