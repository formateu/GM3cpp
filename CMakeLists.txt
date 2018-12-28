cmake_minimum_required(VERSION 3.13)
project(guava_murmurhash3_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(GM3cpp
        src/Murmur3_32.cpp
        src/Murmur3_128.cpp
        src/ByteBuffer.cpp)

add_executable(test_GM3cpp
    tests/test_main.cpp
        tests/test_Murmur3_32.cpp
        )

target_link_libraries(test_GM3cpp
        ${BOOST_UNIT_TEST_FRAMEWORK_LIBRARY}
        GM3cpp
        )
