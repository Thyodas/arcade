cmake_minimum_required(VERSION 3.17)

project(Arcade)

set(CORE_SRCS
    src/main.cpp
    src/Core/Core.cpp
    )

set(NCURSES_SRCS
    src/DisplayModules/ncurses/ncurses.cpp
)

set(SFML_SRCS
    src/DisplayModules/SFML/sfml.cpp
)

set(PACMAN_SRCS
    src/GameModules/pacman/pacman.cpp
)

set(SNAKE_SRCS
    src/GameModules/snake/snake.cpp
)

set(MENU_SRCS
    src/GameModules/Menu/menu.cpp
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++20 -fno-gnu-unique -g")

include_directories(include)

add_library(arcade_ncurses SHARED ${NCURSES_SRCS})
set_target_properties(arcade_ncurses PROPERTIES PREFIX "" SUFFIX ".so")
set_target_properties(arcade_ncurses PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(arcade_sfml SHARED ${SFML_SRCS})
target_link_libraries(arcade_sfml sfml-window sfml-graphics sfml-system)
set_target_properties(arcade_sfml PROPERTIES PREFIX "" SUFFIX ".so")
set_target_properties(arcade_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(arcade_pacman SHARED ${PACMAN_SRCS})
set_target_properties(arcade_pacman PROPERTIES PREFIX "" SUFFIX ".so")
set_target_properties(arcade_pacman PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(arcade_snake SHARED ${SNAKE_SRCS})
set_target_properties(arcade_snake PROPERTIES PREFIX "" SUFFIX ".so")
set_target_properties(arcade_snake PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(arcade_menu SHARED ${MENU_SRCS})
set_target_properties(arcade_menu PROPERTIES PREFIX "" SUFFIX ".so")
set_target_properties(arcade_menu PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(arcade ${CORE_SRCS} ${HEADERS})
set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(arcade dl)

