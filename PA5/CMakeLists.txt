# cmake_minimum_required(VERSION <specify CMake version here>)
project(PA5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Graph.c
        Graph.h
        GraphClient.c
        List.c
        List.h)

add_executable(PA5 ${SOURCE_FILES})