cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_executable(SDL2Test ${all_SRCS})
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})

