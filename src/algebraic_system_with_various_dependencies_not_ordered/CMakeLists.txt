get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

build_executable(${DIR}
    ALGEBRAIC
    INITIAL_VALUES_GUESSES
        "{\"a\", 14.0}, {\"b\", 1.0}, {\"c\", 1.0}, {\"d\", NAN}, {\"x\", 3.0}, {\"y\", 5.0}"
    FINAL_VALUES
        "{\"a\", 14.0}, {\"b\", 4.0}, {\"c\", 7.0}, {\"d\", 11.0}, {\"x\", 3.0}, {\"y\", 5.0}"
)
