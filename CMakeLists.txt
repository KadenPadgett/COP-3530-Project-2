cmake_minimum_required(VERSION 4.4)
project(COP_3530_Project_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COP_3530_Project_2
        Comparisons.h
        LoadSongs.h
        main.cpp
        MergeSort.cpp
        Heapsort.cpp
        Songs.h)
