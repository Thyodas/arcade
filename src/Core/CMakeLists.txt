cmake_minimum_required(VERSION 3.17)

set(CORE_SRCS
    ../main.cpp
    Core.cpp
    )

include(../../Utils.cmake)
set_compilation_flags()

add_executable(arcade ${CORE_SRCS} ${HEADERS})
set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                      ${CMAKE_CURRENT_SOURCE_DIR}/../../)
target_link_libraries(arcade dl)
