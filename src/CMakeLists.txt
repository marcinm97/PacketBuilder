cmake_minimum_required(VERSION 3.15)
add_library(packet_builder INTERFACE)
target_include_directories(packet_builder INTERFACE src/PacketBuilder.h)

add_executable(PacketBuilder main.cpp)
target_compile_options(PacketBuilder PUBLIC -Wall -Wextra -Wpedantic )

target_link_libraries(PacketBuilder packet_builder)