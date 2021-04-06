cmake_minimum_required(VERSION 3.17)
project(eslab1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(eslab1
        hal.h
        main.cpp)
