cmake_minimum_required(VERSION 3.3)
project(ProgAlg_exercices)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES src/main.cpp)
add_executable(ProgAlg_exercices ${SOURCE_FILES})