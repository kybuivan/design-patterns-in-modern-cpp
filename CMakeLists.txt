cmake_minimum_required(VERSION 3.5)

project(DesignPatternsInModernCpp LANGUAGES CXX)

enable_testing()

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(cmake/utils.cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(creational)
add_subdirectory(structural)
add_subdirectory(behavioral)
add_subdirectory(architectural)
add_subdirectory(concurrency)
add_subdirectory(principles)
