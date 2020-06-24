cmake_minimum_required(VERSION 3.14)
project(SFMLTest_project)

set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.0)

set(SFML_DIR "SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio main REQUIRED)
set(SFML_libs sfml-system sfml-window sfml-graphics sfml-network sfml-audio sfml-main)
# add_subdirectory(SFML)

# Libraries
add_subdirectory(Physics)

# Main executables
add_executable(SFMLTest main.cpp)
# add_executable(exe2 main2.cpp)
target_link_libraries(SFMLTest doubleI)
target_link_libraries(SFMLTest ${SFML_libs})

# add_subdirectory(Tests)