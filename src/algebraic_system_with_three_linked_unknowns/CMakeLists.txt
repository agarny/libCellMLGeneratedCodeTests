get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

build_executable(${DIR}
    ALGEBRAIC
    INITIAL_VALUES_GUESSES
        "{\"x\", 1.0}, {\"y\", 1.0}, {\"z\", 1.0}"
    FINAL_VALUES
        "{\"x\", 1.0}, {\"y\", -1.0}, {\"z\", 1.0}"
)
