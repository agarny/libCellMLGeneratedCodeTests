function(build_executable EXECUTABLE)
    add_executable(${EXECUTABLE}
        main.c
    )

    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy ${EXECUTABLE} ${CMAKE_BINARY_DIR}/${EXECUTABLE})
endfunction()
