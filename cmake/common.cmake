function(build_executable EXECUTABLE TYPE)
    if(C_TEST)
        include_directories(${CMAKE_CURRENT_SOURCE_DIR})

        set(MAIN_CPP ${CMAKE_CURRENT_BINARY_DIR}/main.cpp)
    endif()

    if(PYTHON_TEST)
        set(MAIN_PY ${CMAKE_BINARY_DIR}/${EXECUTABLE}.py)
    endif()

    if("${TYPE}" STREQUAL "ODE")
        set(OPTIONS
            EXTERNALS
            SKIP_FIRST_OUTPUT_POINT
        )
        set(ONE_VALUE_KEYWORDS
            EXTERNAL_VALUES
            ENDING_POINT
            POINT_INTERVAL
            OUTPUT_POINTS
            RELATIVE_TOLERANCE
            ABSOLUTE_TOLERANCE
        )

        cmake_parse_arguments(ARG "${OPTIONS}" "${ONE_VALUE_KEYWORDS}" "" ${ARGN})

        if(ARG_EXTERNALS)
            set(EXTERNALS 1)
        else()
            set(EXTERNALS 0)
        endif()

        if("${ARG_ENDING_POINT}" STREQUAL "")
            set(ENDING_POINT 1000.0)
        else()
            set(ENDING_POINT ${ARG_ENDING_POINT})
        endif()

        if("${ARG_POINT_INTERVAL}" STREQUAL "")
            set(POINT_INTERVAL 1.0)
        else()
            set(POINT_INTERVAL ${ARG_POINT_INTERVAL})
        endif()

        if("${ARG_RELATIVE_TOLERANCE}" STREQUAL "")
            set(RELATIVE_TOLERANCE 1.0e-7)
        else()
            set(RELATIVE_TOLERANCE ${ARG_RELATIVE_TOLERANCE})
        endif()

        if("${ARG_ABSOLUTE_TOLERANCE}" STREQUAL "")
            set(ABSOLUTE_TOLERANCE 1.0e-7)
        else()
            set(ABSOLUTE_TOLERANCE ${ARG_ABSOLUTE_TOLERANCE})
        endif()

        set(OUTPUT_POINTS "{${ARG_OUTPUT_POINTS}}")

        if(ARG_SKIP_FIRST_OUTPUT_POINT)
            set(SKIP_FIRST_OUTPUT_POINT true)
        else()
            set(SKIP_FIRST_OUTPUT_POINT false)
        endif()

        if("${ARG_OUTPUT_POINTS}" STREQUAL "")
            set(USE_OUTPUT_POINTS false)
        else()
            set(USE_OUTPUT_POINTS true)
        endif()

        set(EXTERNAL_VALUES "{${ARG_EXTERNAL_VALUES}}")

        if(C_TEST)
            configure_file(../main.ode.cpp.in ${MAIN_CPP})
        endif()

        if(PYTHON_TEST)
            set(OUTPUT_POINTS "[${ARG_OUTPUT_POINTS}]")

            if(ARG_SKIP_FIRST_OUTPUT_POINT)
                set(SKIP_FIRST_OUTPUT_POINT True)
            else()
                set(SKIP_FIRST_OUTPUT_POINT False)
            endif()

            if("${ARG_OUTPUT_POINTS}" STREQUAL "")
                set(USE_OUTPUT_POINTS False)
            else()
                set(USE_OUTPUT_POINTS True)
            endif()

            string(REPLACE "{" "[" EXTERNAL_VALUES "${EXTERNAL_VALUES}")
            string(REPLACE "}" "]" EXTERNAL_VALUES "${EXTERNAL_VALUES}")

            configure_file(../main.ode.py.in ${MAIN_PY})
        endif()
    elseif("${TYPE}" STREQUAL "ALGEBRAIC")
        set(OPTIONS
            EXTERNALS
        )
        set(ONE_VALUE_KEYWORDS
            INITIAL_VALUES_GUESSES
            FINAL_VALUES
        )

        cmake_parse_arguments(ARG "${OPTIONS}" "${ONE_VALUE_KEYWORDS}" "" ${ARGN})

        if(ARG_EXTERNALS)
            set(EXTERNALS 1)
        else()
            set(EXTERNALS 0)
        endif()

        set(INITIAL_VALUES_GUESSES "{${ARG_INITIAL_VALUES_GUESSES}}")
        set(FINAL_VALUES "{${ARG_FINAL_VALUES}}")

        if(C_TEST)
            configure_file(../main.algebraic.cpp.in ${MAIN_CPP})
        endif()

        if(PYTHON_TEST)
            string(REPLACE "{" "" INITIAL_VALUES_GUESSES "${ARG_INITIAL_VALUES_GUESSES}")
            string(REPLACE "}" "" INITIAL_VALUES_GUESSES "${INITIAL_VALUES_GUESSES}")
            string(REPLACE "\"," "\":" INITIAL_VALUES_GUESSES "${INITIAL_VALUES_GUESSES}")
            string(REPLACE "NAN" "math.nan" INITIAL_VALUES_GUESSES "${INITIAL_VALUES_GUESSES}")

            set(INITIAL_VALUES_GUESSES "{${INITIAL_VALUES_GUESSES}}")

            string(REPLACE "{" "" FINAL_VALUES "${ARG_FINAL_VALUES}")
            string(REPLACE "}" "" FINAL_VALUES "${FINAL_VALUES}")
            string(REPLACE "\"," "\":" FINAL_VALUES "${FINAL_VALUES}")

            set(FINAL_VALUES "{${FINAL_VALUES}}")

            configure_file(../main.algebraic.py.in ${MAIN_PY})
        endif()
    else()
        message(FATAL_ERROR "The type of the executable must be either `ODE` or `ALGEBRAIC`.")
    endif()

    if(C_TEST)
        add_executable(${EXECUTABLE}
            ../common.cpp

            ${MAIN_CPP}

            model.c
        )

        target_link_libraries(${EXECUTABLE} SUNDIALS::cvode SUNDIALS::kinsol)

        add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy ${EXECUTABLE} ${CMAKE_BINARY_DIR}/${EXECUTABLE})
    endif()
endfunction()
