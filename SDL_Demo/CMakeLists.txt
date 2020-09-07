cmake_minimum_required(VERSION 3.10)
project(SDL_DEMO)


find_package(SDL2)
include_directories(${SDL2_INCLUDE_DIRECTORIES})
add_executable(SDL_PixelRender
	"SDL_PixelRender.cpp"
)
target_include_directories(SDL_PixelRender PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(SDL_PixelRender "SDL2.a" "pthread" "dl")


add_executable(SDL_DrawLines 
	"SDL_RenderDrawLine.cpp"
)

target_include_directories(SDL_DrawLines PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(SDL_DrawLines "SDL2.a" "SDL2_image.a" "pthread" "dl")
add_definitions("-g")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
