build_executable(robertson_model_1966_dae
    ODE
    OUTPUT_POINTS
        "{4.0e-6, 4.0e-5, 4.0e-4, 4.0e-3, 4.0e-2, 4.0e-1, 4.0e0, 4.0e1, 4.0e2, 4.0e3, 4.0e4, 4.0e5}"
    SKIP_FIRST_OUTPUT_POINT
    RELATIVE_TOLERANCE
        1.0e-10
    ABSOLUTE_TOLERANCE
        1.0e-14
)
