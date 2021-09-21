cmake_minimum_required(VERSION 3.0)

project(Mana)

set(TARGET mana)

file(GLOB SRC_FILES src/*.cpp)

find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIR})

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