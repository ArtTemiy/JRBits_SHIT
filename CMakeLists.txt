cmake_minimum_required(VERSION 3.14)
project(SFMLTest_project)

set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0)

# SFML
set(SFML_DIR "SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics network audio main REQUIRED)
set(SFML_lib sfml-system sfml-window sfml-graphics sfml-network sfml-audio sfml-main)

# Libraries
add_subdirectory(Physics)
set(physics_libs
        double_i_lib
        vectorNd_lib
        object_lib
        world_lib)

add_library(drawable_lib "drawable.cpp")
target_link_libraries(drawable_lib ${SFML_lib})
target_link_libraries(drawable_lib ${physics_libs})
add_library(utils_lib "Utils/utils.cpp")
target_link_libraries(utils_lib ${SFML_lib})
target_link_libraries(utils_lib drawable_lib)
target_link_libraries(utils_lib ${physics_libs})

set(all_libs
    ${SFML_lib}
    ${physics_libs}
    drawable_lib
    utils_lib)

# Main executables
add_executable(Game main.cpp)
target_link_libraries(Game ${physics_libs})
target_link_libraries(Game utils_lib)
target_link_libraries(Game drawable_lib)
target_link_libraries(Game ${SFML_lib})

# Help executable
add_executable(main_for_test cpp_for_testing.cpp)
target_link_libraries(main_for_test utils_lib)

# TESTS
add_executable(memory_leaks_test "Tests/memory_leaks.cpp")
target_link_libraries(memory_leaks_test ${all_libs})
add_executable(collisions_test "Tests/collisions.cpp")
target_link_libraries(collisions_test ${all_libs})