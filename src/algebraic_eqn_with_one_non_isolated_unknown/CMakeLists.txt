get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

build_executable(${DIR}
    ALGEBRAIC
    INITIAL_VALUES_GUESSES
        "{\"a\", 1.0}, {\"b\", 3.0}, {\"c\", 5.0}, {\"d\", 7.0}"
    FINAL_VALUES
        "{\"a\", 9.0}, {\"b\", 3.0}, {\"c\", 5.0}, {\"d\", 7.0}"
)
