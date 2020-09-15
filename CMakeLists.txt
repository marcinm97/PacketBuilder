cmake_minimum_required(VERSION 3.15)
project(PacketBuilder)

option(BUILD_TESTS OFF)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

add_subdirectory(tests)
set(CMAKE_CXX_STANDARD 17)

add_library(packet_builder INTERFACE)
target_include_directories(packet_builder INTERFACE inc)

add_executable(PacketBuilder src/main.cpp)

target_compile_options(PacketBuilder PUBLIC -Wall -Wextra -Wpedantic )

target_link_libraries(PacketBuilder packet_builder)


