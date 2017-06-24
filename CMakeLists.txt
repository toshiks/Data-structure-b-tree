cmake_minimum_required(VERSION 3.6)
project(B_tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES main.cpp str.h str.cpp B+tree\B+tree.h B+tree\B+tree.cpp)
add_executable(B_tree ${SOURCE_FILES})