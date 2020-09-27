cmake_minimum_required(VERSION 3.10)
project(GBSim)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRECTORIES})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp
		    ${PROJECT_SOURCE_DIR}/Instructions/*.cpp)


add_executable(GB ${SRC_FILES})
target_include_directories(GB PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(GB "SDL2" "stdc++fs")
add_definitions("-g")

set_target_properties(GB PROPERTIES 
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory("SDL_Demo")
