cmake_minimum_required( VERSION 3.7.0 )
project( sdl2-demo )

set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory( external/SDL )

add_executable(
    ${PROJECT_NAME}
    "src/main.cpp"
    )
target_link_libraries( ${PROJECT_NAME} SDL2main SDL2-static )
