cmake_minimum_required(VERSION 3.17)

set(SDL2_SRCS
    sdl2.cpp
    )

include(../../../Utils.cmake)
set_compilation_flags()

add_library(arcade_sdl2 SHARED ${SDL2_SRCS})
find_package(SDL2 REQUIRED COMPONENTS SDL2)
if (APPLE)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    target_link_libraries(arcade_sdl2 SDL2::SDL2 SDL2_image::SDL2_image
                          SDL2_ttf::SDL2_ttf)
else()
    target_link_libraries(arcade_sdl2 SDL2 SDL2_image SDL2_ttf)
endif()
include_directories(${SDL2_INCLUDE_DIRS})

set_lib_target(arcade_sdl2)
