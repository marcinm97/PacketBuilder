cmake_minimum_required(VERSION 3.15)
add_subdirectory(googletest)
enable_testing()

add_executable(tests PacketBuilderTests.cpp)

target_link_libraries(tests PRIVATE
                            gtest_main
                            packet_builder)