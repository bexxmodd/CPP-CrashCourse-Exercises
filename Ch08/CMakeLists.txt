cmake_minimum_required(VERSION 3.20)
project(Ch08)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(Ch08
        main.cpp
        Primes.h)
