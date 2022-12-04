cmake_minimum_required(VERSION 3.23)
project(234124_ex2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(234124_ex2
        Card.cpp
        Card.h
        Mtmchkin.cpp
        Mtmchkin.h
        Player.cpp
        Player.h
        test.cpp
        utilities.cpp
        utilities.h)
