cmake_minimum_required(VERSION 3.17)

set(MENU_SRCS
    menu.cpp
    )

include(../../../Utils.cmake)
set_compilation_flags()

add_library(arcade_menu SHARED ${MENU_SRCS})
set_lib_target(arcade_menu)
