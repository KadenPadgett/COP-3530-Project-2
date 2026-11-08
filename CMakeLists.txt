cmake_minimum_required(VERSION 4.2.2)

project(COP_3530_Project_2)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
        FLTK
        GIT_REPOSITORY https://github.com/fltk/fltk.git
        GIT_TAG release-1.4.4
)

FetchContent_MakeAvailable(FLTK)

add_executable(COP_3530_Project_2
        Comparisons.h
        LoadSongs.h
        main.cpp
        MergeSort.cpp
        Heapsort.cpp
        Songs.h
)

target_link_libraries(COP_3530_Project_2 PRIVATE fltk)