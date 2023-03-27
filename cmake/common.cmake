function(build_executable EXECUTABLE)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    add_executable(${EXECUTABLE}
        ../algebraicmodel.cpp
        ../common.cpp

        main.cpp
        model.c
    )

    target_link_libraries(${EXECUTABLE} SUNDIALS::cvode SUNDIALS::kinsol)

    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy ${EXECUTABLE} ${CMAKE_BINARY_DIR}/${EXECUTABLE})
endfunction()
