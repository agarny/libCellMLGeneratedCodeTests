list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(common)

find_package(SUNDIALS REQUIRED cvode kinsol)

include_directories(.)

add_subdirectory(algebraic_eqn_with_one_non_isolated_unknown)
add_subdirectory(algebraic_system_with_three_linked_unknowns)
