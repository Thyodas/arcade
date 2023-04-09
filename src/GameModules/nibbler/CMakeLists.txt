cmake_minimum_required(VERSION 3.17)

set(NIBBLER_SRCS
    nibbler.cpp
    )

include(../../../Utils.cmake)
set_compilation_flags()

add_library(arcade_nibbler SHARED ${NIBBLER_SRCS})
set_lib_target(arcade_nibbler)
