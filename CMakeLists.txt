cmake_minimum_required(VERSION 3.26)
project(persistenttree)

set(CMAKE_CXX_STANDARD 17)

add_executable(persistenttree main.cpp
        persistentTree.cpp
        Point.h
        Rectangle.cpp
        Rectangle.h
        MAPAlgo.cpp
        MAPAlgo.h
        constants.cpp
        constants.h
)
