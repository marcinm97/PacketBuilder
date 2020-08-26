cmake_minimum_required(VERSION 3.15)
project(PacketBuilder)
option(BUILD_TESTS OFF)

message(${BUILD_TESTS})
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(tests)

