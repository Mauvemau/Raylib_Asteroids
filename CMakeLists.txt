cmake_minimum_required(VERSION 3.27)
project(Astray)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(src)
add_executable(Astray ${SOURCES})

find_package(raylib 5.0 REQUIRED)

target_link_libraries(Astray PRIVATE raylib)
