include_guard()

function(set_compilation_flags)
    if (APPLE)
        set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++20 -g" PARENT_SCOPE)
        include_directories(/usr/local/include)
        link_directories(/usr/local/lib)
    else()
        set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++20 -fno-gnu-unique -g" PARENT_SCOPE)
    endif()
    include_directories(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/include)
endfunction()

function(set_lib_target target)
    set_target_properties(${target} PROPERTIES PREFIX "" SUFFIX ".so")
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                          ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/lib)
endfunction()
