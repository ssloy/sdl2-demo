cmake_minimum_required( VERSION 3.7.0 )
project( sdl2-demo )

set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory( external/SDL )

add_executable(
    sdl2-demo
    "src/main.cpp"
    )
target_link_libraries( sdl2-demo SDL2main SDL2-static )
