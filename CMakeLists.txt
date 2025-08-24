cmake_minimum_required(VERSION 3.10)
project(shunt-header-only LANGUAGES CXX)

# Make sure we export the compile commands for Emacs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Header-only library, so no targets to build: only install target
install(
  FILES shunt.hpp
  DESTINATION include
)

# Enable tests with Catch2
enable_testing()
find_package(Catch2 3 REQUIRED)

add_executable(shunt_test tests/test_shunt.cpp)
target_include_directories(shunt_test PRIVATE src/)
target_link_libraries(shunt_test PRIVATE Catch2::Catch2WithMain)

add_test(NAME run_tests COMMAND shunt_test)
