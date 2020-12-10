# CMakeLists.txt

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

project(Conway)

# Use C++11 (required by Catch2 library)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Game of Life runner
add_executable(Conway
  src/conway.cpp
  src/GridWorld.cpp
)
target_compile_options(Conway PRIVATE -Wall -Werror)
target_include_directories(Conway PUBLIC
  inc
)

# Catch2 Unit Tests
find_package(Catch2 REQUIRED)
add_executable(Tests
  tests/test.cpp
  src/GridWorld.cpp
)
target_compile_options(Tests PRIVATE -Wall -Werror)
target_include_directories(Tests PUBLIC
  inc
)
target_link_libraries(Tests Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(Tests)
