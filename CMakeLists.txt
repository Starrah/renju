cmake_minimum_required(VERSION 3.15)
project(renju)

set(CMAKE_CXX_STANDARD 14)

include_directories(renju)

add_executable(renju
        renju/createmoves.cpp
        renju/createmoves.h
        renju/define.cpp
        renju/define.h
        renju/evaluate.cpp
        renju/evaluate.h
        renju/gameover.cpp
        renju/makemove.cpp
        renju/makemove.h
        renju/printchessboard.cpp
        renju/printchessboard.h
        renju/searchmove.cpp
        renju/searchmove.h
        renju/start.cpp
        )

target_link_libraries(renju)