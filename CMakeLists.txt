cmake_minimum_required(VERSION 3.18.0)

project(libCellMLGeneratedCodeTests)

if("${TEST}" STREQUAL "" OR "${TEST}" STREQUAL "ALL")
    set(C_TEST ON)
    set(PYTHON_TEST ON)
elseif("${TEST}" STREQUAL "C")
    set(C_TEST ON)
elseif("${TEST}" STREQUAL "PYTHON")
    set(PYTHON_TEST ON)
else()
    message(FATAL_ERROR "The TEST option cannot be equal to '${TEST}'. Possible values are 'ALL' (default), 'C', and 'PYTHON'.")
endif()

if(C_TEST)
    message(STATUS "C tests enabled")
else()
    message(STATUS "C tests NOT enabled")
endif()

if(PYTHON_TEST)
    message(STATUS "Python tests enabled")
else()
    message(STATUS "Python tests NOT enabled")
endif()

add_subdirectory(src)
