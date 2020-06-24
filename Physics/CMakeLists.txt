cmake_minimum_required(VERSION 3.14)
project(Physics)

set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0)
add_library(doubleI double_i.cpp)
add_library(vectorNd vectorNd.cpp)

add_library(physics STATIC physics.h)

target_link_libraries(physics
        doubleI
        vectorNd)

# TESTS
add_subdirectory(Tests)