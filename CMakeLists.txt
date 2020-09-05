cmake_minimum_required(VERSION 3.10)
project(GBSim)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)


add_executable(GB ${SRC_FILES})
target_include_directories(GB PUBLIC ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
