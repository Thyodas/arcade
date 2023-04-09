cmake_minimum_required(VERSION 3.17)

set(NCURSES_SRCS
    ncurses.cpp
    )

include(../../../Utils.cmake)
set_compilation_flags()

add_library(arcade_ncurses SHARED ${NCURSES_SRCS})
target_link_libraries(arcade_ncurses ncurses)
set_lib_target(arcade_ncurses)
