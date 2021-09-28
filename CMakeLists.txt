cmake_minimum_required(VERSION 3.0)

project(Mana VERSION 0.1)

set(TARGET mana)

add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

option(MINGW_OSX "Mingw build for WIN32 on OSX" ON)

if (MINGW_OSX)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    set(CMAKE_CXX_LINK_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIR})

include_directories(src/)

add_executable(
    ${TARGET}
    ${SRC_FILES}
)

if (APPLE)
    target_link_libraries(
        ${TARGET}
        ${LLVM_LIBRARIES}
        )
elseif(UNIX)
    target_link_libraries(
        ${TARGET}
        ${LLVM_LIBRARIES}
        )
elseif(MINGW)
    target_link_libraries(
        ${TARGET}
        ${LLVM_LIBRARIES}
        )
endif()