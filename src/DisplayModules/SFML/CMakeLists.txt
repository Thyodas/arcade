cmake_minimum_required(VERSION 3.17)

set(SFML_SRCS
    sfml.cpp
    )

include(../../../Utils.cmake)
set_compilation_flags()

add_library(arcade_sfml SHARED ${SFML_SRCS})
target_link_libraries(arcade_sfml sfml-window sfml-graphics sfml-system)
set_lib_target(arcade_sfml)
