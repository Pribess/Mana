cmake_minimum_required(VERSION 3.0)

project(Mana VERSION 0.0.1)

set(TARGET mana)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

include_directories(src/)

add_executable(
    ${TARGET}
    ${SRC_FILES}
)