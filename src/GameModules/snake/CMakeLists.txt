cmake_minimum_required(VERSION 3.17)

set(SNAKE_SRCS
    snake.cpp
    )

include(../../../Utils.cmake)
set_compilation_flags()

add_library(arcade_snake SHARED ${SNAKE_SRCS})
set_lib_target(arcade_snake)
