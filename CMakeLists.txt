# CMakeLists.txt

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

project(conway)

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

# Copy world files
add_custom_command(TARGET Conway POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/worlds/
                   $<TARGET_FILE_DIR:Conway>)

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

# Copy test worlds to the output directory
add_custom_command(TARGET Tests POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/tests/test_worlds/
                   $<TARGET_FILE_DIR:Tests>)
