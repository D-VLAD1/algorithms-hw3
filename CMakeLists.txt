cmake_minimum_required(VERSION 4.0)
project(algorithms_hw3 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(algorithms_hw3 src/main.cpp
        include/maxflow.cpp)