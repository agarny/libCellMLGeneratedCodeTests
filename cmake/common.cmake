function(build_executable EXECUTABLE TYPE)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    set(MAIN_CPP ${CMAKE_CURRENT_BINARY_DIR}/main.cpp)

    if("${TYPE}" STREQUAL "ALGEBRAIC")
        list(LENGTH ARGN ARGN_COUNT)

        if(ARGN_COUNT EQUAL 2)
            list(GET ARGN 0 INITIAL_VARIABLE_VALUES_GUESSES)
            list(GET ARGN 1 FINAL_VARIABLE_VALUES)
        endif ()

        configure_file(../main.algebraic.cpp.in ${MAIN_CPP})
    endif()

    add_executable(${EXECUTABLE}
        ../common.cpp

        ${MAIN_CPP}

        model.c
    )

    target_link_libraries(${EXECUTABLE} SUNDIALS::cvode SUNDIALS::kinsol)

    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy ${EXECUTABLE} ${CMAKE_BINARY_DIR}/${EXECUTABLE})
endfunction()
