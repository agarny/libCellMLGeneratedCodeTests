if(C_TEST)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(common)

if(C_TEST)
    find_package(SUNDIALS REQUIRED cvode kinsol)

    include_directories(.)
endif()

if(PYTHON_TEST)
    configure_file(common.py ${CMAKE_BINARY_DIR}/common.py)
endif()

file(GLOB ITEMS LIST_DIRECTORIES TRUE "*")

foreach(ITEM ${ITEMS})
    if(IS_DIRECTORY ${ITEM})
        add_subdirectory(${ITEM})
    endif()
endforeach()
