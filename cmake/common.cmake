function(build_executable EXECUTABLE TYPE)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    set(MAIN_CPP ${CMAKE_CURRENT_BINARY_DIR}/main.cpp)

    if("${TYPE}" STREQUAL "ODE")
        list(LENGTH ARGN ARGN_COUNT)

        if(ARGN_COUNT EQUAL 5)
            list(GET ARGN 0 ENDING_POINT)
            list(GET ARGN 1 POINT_INTERVAL)
            list(GET ARGN 2 MAXIMUM_STEP)
            list(GET ARGN 3 RELATIVE_TOLERANCE)
            list(GET ARGN 4 ABSOLUTE_TOLERANCE)

            configure_file(../main.ode.cpp.in ${MAIN_CPP})
        else()
            message(FATAL_ERROR "The `ODE` type requires an ending point, a point interval, a maximum step, a relative tolerance, and an absolute tolerance.")
        endif ()
    elseif("${TYPE}" STREQUAL "ALGEBRAIC")
        list(LENGTH ARGN ARGN_COUNT)

        if(ARGN_COUNT EQUAL 2)
            list(GET ARGN 0 INITIAL_VARIABLE_VALUES_GUESSES)
            list(GET ARGN 1 FINAL_VARIABLE_VALUES)

            configure_file(../main.algebraic.cpp.in ${MAIN_CPP})
        else()
            message(FATAL_ERROR "The `ALGEBRAIC` type requires some initial variable values/guesses and some final variable values.")
        endif ()
    else()
        message(FATAL_ERROR "The type of the executable must be either `ODE` or `ALGEBRAIC`.")
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
