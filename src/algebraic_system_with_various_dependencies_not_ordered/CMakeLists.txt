build_executable(algebraic_system_with_various_dependencies_not_ordered
    ALGEBRAIC
    INITIAL_VARIABLE_VALUES_GUESSES
        "{\"a\", 14.0}, {\"b\", 1.0}, {\"c\", 1.0}, {\"d\", NAN}, {\"x\", 3.0}, {\"y\", 5.0}"
    FINAL_VARIABLE_VALUES
        "{\"a\", 14.0}, {\"b\", 4.0}, {\"c\", 7.0}, {\"d\", 11.0}, {\"x\", 3.0}, {\"y\", 5.0}"
)
