cmake_minimum_required(VERSION 3.14)
project(Physics)

set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0)

add_library(double_i_lib double_i.cpp)

add_library(vectorNd_lib vectorNd.cpp)
target_link_libraries(vectorNd_lib double_i_lib)

add_library(object_lib object.cpp)
target_link_libraries(object_lib double_i_lib)

add_library(world_lib world.cpp)
target_link_libraries(world_lib
	double_i_lib
	vectorNd_lib
	object_lib)

# TESTS
add_subdirectory(Tests)