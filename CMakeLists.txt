cmake_minimum_required(VERSION 3.13)
project(guava_murmurhash3_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(guava_murmurhash3_cpp
        Murmur3_32.cpp
        Murmur3_32.hpp
        MurmurHash3.cpp
        MurmurHash3.h
        main.cpp)

