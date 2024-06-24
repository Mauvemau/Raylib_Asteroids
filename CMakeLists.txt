cmake_minimum_required(VERSION 3.27)
project(RaylibAsteroids)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(src)
add_executable(RaylibAsteroids ${SOURCES})

find_package(raylib 5.0 REQUIRED)

target_link_libraries(RaylibAsteroids PRIVATE raylib)
