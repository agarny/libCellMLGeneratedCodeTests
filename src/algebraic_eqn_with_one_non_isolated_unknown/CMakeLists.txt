build_executable(algebraic_eqn_with_one_non_isolated_unknown
    ALGEBRAIC
    INITIAL_VARIABLE_VALUES_GUESSES
        "{{\"a\", 1.0}, {\"b\", 3.0}, {\"c\", 5.0}, {\"d\", 7.0}}"
    FINAL_VARIABLE_VALUES
        "{{\"a\", 9.0}, {\"b\", 3.0}, {\"c\", 5.0}, {\"d\", 7.0}}"
)
