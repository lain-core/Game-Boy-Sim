cmake_minimum_required(VERSION 3.10)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRECTORIES})

add_executable(pixelmod "pixelmod.cpp")

target_link_libraries(pixelmod "SDL2")

add_executable(SDLdemo "SDLdemo.cpp")

target_link_libraries(SDLdemo "SDL2")

add_executable(SDL_keyInput "SDL_keyInput.cpp")

target_link_libraries(SDL_keyInput "SDL2")
