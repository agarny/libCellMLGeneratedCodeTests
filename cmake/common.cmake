function(build_executable EXECUTABLE TYPE)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    set(MAIN_CPP ${CMAKE_CURRENT_BINARY_DIR}/main.cpp)
    set(MAIN_PY ${CMAKE_BINARY_DIR}/${EXECUTABLE}.py)

    if("${TYPE}" STREQUAL "ODE")
        set(OPTIONS
            SKIP_FIRST_OUTPUT_POINT
        )
        set(ONE_VALUE_KEYWORDS
            ENDING_POINT
            POINT_INTERVAL
            OUTPUT_POINTS
            RELATIVE_TOLERANCE
            ABSOLUTE_TOLERANCE
        )

        cmake_parse_arguments(ARG "${OPTIONS}" "${ONE_VALUE_KEYWORDS}" "" ${ARGN})

        if("${ARG_ENDING_POINT}" STREQUAL "")
            set(ARG_ENDING_POINT 1000.0)
        endif()

        if("${ARG_POINT_INTERVAL}" STREQUAL "")
            set(ARG_POINT_INTERVAL 1.0)
        endif()

        if("${ARG_OUTPUT_POINTS}" STREQUAL "")
            set(ARG_USE_OUTPUT_POINTS false)
        else()
            set(ARG_USE_OUTPUT_POINTS true)
        endif()

        set(ARG_OUTPUT_POINTS_CPP "{${ARG_OUTPUT_POINTS}}")
        set(ARG_OUTPUT_POINTS_PYTHON "[${ARG_OUTPUT_POINTS}]")

        if(ARG_SKIP_FIRST_OUTPUT_POINT)
            set(ARG_SKIP_FIRST_OUTPUT_POINT true)
        else()
            set(ARG_SKIP_FIRST_OUTPUT_POINT false)
        endif()

        if("${ARG_RELATIVE_TOLERANCE}" STREQUAL "")
            set(ARG_RELATIVE_TOLERANCE 1.0e-7)
        endif()

        if("${ARG_ABSOLUTE_TOLERANCE}" STREQUAL "")
            set(ARG_ABSOLUTE_TOLERANCE 1.0e-7)
        endif()

        configure_file(../main.ode.cpp.in ${MAIN_CPP})
        configure_file(../main.ode.py.in ${MAIN_PY})
    elseif("${TYPE}" STREQUAL "ALGEBRAIC")
        set(ONE_VALUE_KEYWORDS
            INITIAL_VARIABLE_VALUES_GUESSES
            FINAL_VARIABLE_VALUES
        )

        cmake_parse_arguments(ARG "" "${ONE_VALUE_KEYWORDS}" "" ${ARGN})

        set(ARG_INITIAL_VARIABLE_VALUES_GUESSES_CPP "{${ARG_INITIAL_VARIABLE_VALUES_GUESSES}}")

        string(REPLACE "{" "" ARG_INITIAL_VARIABLE_VALUES_GUESSES "${ARG_INITIAL_VARIABLE_VALUES_GUESSES}")
        string(REPLACE "}" "" ARG_INITIAL_VARIABLE_VALUES_GUESSES "${ARG_INITIAL_VARIABLE_VALUES_GUESSES}")
        string(REPLACE "\"," "\":" ARG_INITIAL_VARIABLE_VALUES_GUESSES "${ARG_INITIAL_VARIABLE_VALUES_GUESSES}")

        set(ARG_INITIAL_VARIABLE_VALUES_GUESSES_PYTHON "{${ARG_INITIAL_VARIABLE_VALUES_GUESSES}}")

        set(ARG_FINAL_VARIABLE_VALUES_CPP "{${ARG_FINAL_VARIABLE_VALUES}}")

        string(REPLACE "{" "" ARG_FINAL_VARIABLE_VALUES "${ARG_FINAL_VARIABLE_VALUES}")
        string(REPLACE "}" "" ARG_FINAL_VARIABLE_VALUES "${ARG_FINAL_VARIABLE_VALUES}")
        string(REPLACE "\"," "\":" ARG_FINAL_VARIABLE_VALUES "${ARG_FINAL_VARIABLE_VALUES}")

        set(ARG_FINAL_VARIABLE_VALUES_PYTHON "{${ARG_FINAL_VARIABLE_VALUES}}")

        configure_file(../main.algebraic.cpp.in ${MAIN_CPP})
        configure_file(../main.algebraic.py.in ${MAIN_PY})
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
