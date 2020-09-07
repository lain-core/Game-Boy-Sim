cmake_minimum_required(VERSION 3.10)
project(GBSim)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRECTORIES})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)


add_executable(GB ${SRC_FILES})
target_include_directories(GB PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(GB "SDL2")
add_definitions("-g")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
