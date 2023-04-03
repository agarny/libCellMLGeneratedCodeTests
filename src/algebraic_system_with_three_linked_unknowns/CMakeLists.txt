build_executable(algebraicSystemWithThreeLinkedUnknowns
    ALGEBRAIC
    INITIAL_VARIABLE_VALUES_GUESSES
        "{{\"x\", 1.0}, {\"y\", 1.0}, {\"z\", 1.0}}"
    FINAL_VARIABLE_VALUES
        "{{\"x\", 1.0}, {\"y\", -1.0}, {\"z\", 1.0}}"
)
