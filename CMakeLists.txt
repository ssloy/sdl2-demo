cmake_minimum_required( VERSION 3.7.0 )
project( sdl2-demo )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external)

if (MSVC)
    # warning level 4 (and all warnings as errors, /WX)
    add_compile_options(/W4)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_definitions(-DRESOURCES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/resources/\")
add_executable(
    ${PROJECT_NAME}
    "src/main.cpp"
    )
target_include_directories(${PROJECT_NAME} PRIVATE "external/SDL/include")
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    SDL2main
    SDL2-static
    )
