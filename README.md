This repository can be used to test the C and/or Python codes generated by [libCellML](https://github.com/cellml/libcellml) for some algebraic, ODE, and DAE models with and without external variables.

**Prerequisites:**
- [CMake](https://cmake.org/);
- [SUNDIALS](https://computing.llnl.gov/projects/sundials) (for the C tests); and
- [SciPy](https://scipy.org/) (for the Python tests).

**Configuration:**
```bash
# Create a build directory:

mkdir build
cd build

# Configure using the default generator:

cmake ..                        # Configure all the tests.
cmake .. -DTEST=ALL             # Configure all the tests.
cmake .. -DTEST=C               # Only configure the C tests.
cmake .. -DTEST=PYTHON          # Only configure the Python tests.

# Configure using the Ninja generator:

cmake -G Ninja ..               # Configure all the tests.
cmake -G Ninja .. -DTEST=ALL    # Configure all the tests.
cmake -G Ninja .. -DTEST=C      # Only configure the C tests.
cmake -G Ninja .. -DTEST=PYTHON # Only configure the Python tests.
```

**Build:** _(only needed for the C tests)_
```bash
cmake --build .
```

**C tests:**
```bash
./<c_test>
```

**Python tests:**
```bash
python <python_test>
```

All tests output some general information about themselves to the console. Algebraic tests also output their solution to the console and compare it with the known solution. ODE and DAE tests generate a [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) file of the form `<test>___c.csv` for the C tests and `<test>___python.csv` for the Python tests.
