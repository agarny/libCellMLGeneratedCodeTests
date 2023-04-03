build_executable(robertson_model_1966_dae
    ODE
    OUTPUT_POINTS
        "{0.4, 4.0, 40.0, 400.0, 4.0e3, 4.0e4, 4.0e5, 4.0e6, 4.0e7, 4.0e8, 4.0e9, 4.0e10}"
    RELATIVE_TOLERANCE
        1.0e-10
    ABSOLUTE_TOLERANCE
        1.0e-14
)
