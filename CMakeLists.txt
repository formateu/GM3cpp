cmake_minimum_required(VERSION 3.10)
project(GM3cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -Wall -Wextra --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")


include_directories(GM3cpp)

add_library(GM3cpp SHARED
        src/Murmur3_32.cpp
        src/Murmur3_128.cpp
        src/ByteBuffer.cpp)

add_executable(examples
        EXCLUDE_FROM_ALL
        examples/test_main.cpp
        examples/test_Murmur3_32.cpp
        examples/test_Murmur3_128.cpp
        )

target_link_libraries(examples
        ${BOOST_UNIT_TEST_FRAMEWORK_LIBRARY}
        GM3cpp
        )
