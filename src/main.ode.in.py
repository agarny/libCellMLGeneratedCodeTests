import importlib.util
from scipy.integrate import solve_ivp
import os


EXTERNALS = @EXTERNALS@


def external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, index):
    external_values = @EXTERNAL_VALUES@

    for i in range(0, len(external_values)-1):
        voi0 = external_values[i][0]
        voi1 = external_values[i+1][0]

        if (voi >= voi0) and (voi < voi1):
            value0 = external_values[i][index+1]

            return value0 + (voi-voi0)/(voi1-voi0)*(external_values[i+1][index+1]-value0)

    return external_values[-1][index+1]


def variable_type(type):
    if type == model.VariableType.VARIABLE_OF_INTEGRATION:
        return "variable of integration"
    elif type == model.VariableType.STATE:
        return "state"
    elif type == model.VariableType.CONSTANT:
        return "constant"
    elif type == model.VariableType.COMPUTED_CONSTANT:
        return "computed constant"
    else:
        return "algebraic"


def print_information(model):
    print("---------------------------------------[Information][BEGIN]")
    print(f"- Generator version: {model.__version__}")
    print(f"- libCellML version: {model.LIBCELLML_VERSION}")
    print("---------------------------------------")
    print("- Variable of integration:")
    print(f"   - {model.VOI_INFO['component']}.{model.VOI_INFO['name']} [{model.VOI_INFO['units']}]")
    print("---------------------------------------")
    print(f"- Number of states: {model.STATE_COUNT}")

    if model.STATE_COUNT > 0:
        for i in range(0, model.STATE_COUNT):
            print(
                f"   - {model.STATE_INFO[i]['name']} [{model.STATE_INFO[i]['units']}] [{model.STATE_INFO[i]['component']}]"
            )

    print("---------------------------------------")
    print(f"- Number of constants: {model.CONSTANT_COUNT}")

    if model.CONSTANT_COUNT > 0:
        for i in range(0, model.CONSTANT_COUNT):
            print(
                f"   - {model.CONSTANT_INFO[i]['name']} [{model.CONSTANT_INFO[i]['units']}] [{model.CONSTANT_INFO[i]['component']}]"
            )

    print("---------------------------------------")
    print(f"- Number of computed constants: {model.COMPUTED_CONSTANT_COUNT}")

    if model.COMPUTED_CONSTANT_COUNT > 0:
        for i in range(0, model.COMPUTED_CONSTANT_COUNT):
            print(
                f"   - {model.COMPUTED_CONSTANT_INFO[i]['name']} [{model.COMPUTED_CONSTANT_INFO[i]['units']}] [{model.COMPUTED_CONSTANT_INFO[i]['component']}]"
            )

    print("---------------------------------------")
    print(f"- Number of algebraic variables: {model.ALGEBRAIC_COUNT}")

    if model.ALGEBRAIC_COUNT > 0:
        for i in range(0, model.ALGEBRAIC_COUNT):
            print(
                f"   - {model.ALGEBRAIC_INFO[i]['name']} [{model.ALGEBRAIC_INFO[i]['units']}] [{model.ALGEBRAIC_INFO[i]['component']}]"
            )

    if EXTERNALS:
        print("---------------------------------------")
        print(f"- Number of external variables: {model.EXTERNAL_COUNT}")

        if model.EXTERNAL_COUNT > 0:
            for i in range(0, model.EXTERNAL_COUNT):
                print(
                    f"   - {model.EXTERNAL_INFO[i]['name']} [{model.EXTERNAL_INFO[i]['units']}] [{model.EXTERNAL_INFO[i]['component']}]"
                )

    print("---------------------------------------[Information][END]")


def print_headers(file):
    file.write("voi")

    for i in range(0, model.STATE_COUNT):
        file.write(f",{model.STATE_INFO[i]['name']}")

    for i in range(0, model.CONSTANT_COUNT):
        file.write(f",{model.CONSTANT_INFO[i]['name']}")

    for i in range(0, model.COMPUTED_CONSTANT_COUNT):
        file.write(f",{model.COMPUTED_CONSTANT_INFO[i]['name']}")

    for i in range(0, model.ALGEBRAIC_COUNT):
        file.write(f",{model.ALGEBRAIC_INFO[i]['name']}")

    if EXTERNALS:
        for i in range(0, model.EXTERNAL_COUNT):
            file.write(f",{model.EXTERNAL_INFO[i]['name']}")

    file.write("\n")


def print_values(file, voi, states, constants, computed_constants, algebraic, externals=None):
    file.write(f"{voi}")

    for i in range(0, model.STATE_COUNT):
        file.write(f",{states[i]}")

    for i in range(0, model.CONSTANT_COUNT):
        file.write(f",{constants[i]}")

    for i in range(0, model.COMPUTED_CONSTANT_COUNT):
        file.write(f",{computed_constants[i]}")

    for i in range(0, model.ALGEBRAIC_COUNT):
        file.write(f",{algebraic[i]}")

    if EXTERNALS:
        for i in range(0, model.EXTERNAL_COUNT):
            file.write(f",{externals[i]}")

    file.write("\n")


def func(t, states, rates, constants, computed_constants, algebraic, externals=None, external_variable=None):
    if EXTERNALS:
        model.compute_rates(t, states, rates, constants, computed_constants, algebraic, externals, external_variable)
    else:
        model.compute_rates(t, states, rates, constants, computed_constants, algebraic)

    return rates


# Load our model.

spec = importlib.util.spec_from_file_location(
    "model", "${CMAKE_SOURCE_DIR}/src/@EXECUTABLE@/model.py"
)
model = importlib.util.module_from_spec(spec)

spec.loader.exec_module(model)

# Some information about the model.

print_information(model)

# Create our various arrays.

voi = 0.0
states = model.create_states_array()
rates = model.create_states_array()
constants = model.create_constants_array()
computed_constants = model.create_computed_constants_array()
algebraic = model.create_algebraic_array()

if EXTERNALS:
    externals = model.create_externals_array()

# Initialise our constants, computed constants, and algebraic variables and output their initial value/guess.

model.initialise_variables(states, rates, constants, computed_constants, algebraic)
model.compute_computed_constants(states, rates, constants, computed_constants, algebraic)

if EXTERNALS:
    model.compute_rates(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable)
    model.compute_variables(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable)
else:
    model.compute_rates(voi, states, rates, constants, computed_constants, algebraic)
    model.compute_variables(voi, states, rates, constants, computed_constants, algebraic)

file = open(os.path.join(os.path.dirname(__file__), "@EXECUTABLE@___python.csv"), "w")

print_headers(file)

if not @SKIP_FIRST_OUTPUT_POINT@:
    if EXTERNALS:
        print_values(file, voi, states, constants, computed_constants, algebraic, externals)
    else:
        print_values(file, voi, states, constants, computed_constants, algebraic)

# Run our model.

output_points = @OUTPUT_POINTS@

if not False:
    i = 0
    voi_max = @ENDING_POINT@
    voi_interval = @POINT_INTERVAL@

    while True:
        i += 1
        voi = i * voi_interval

        output_points.append(voi)

        if voi >= voi_max:
            break

voi = 0.0

for output_point in output_points:
    # Integrate our model.

    if EXTERNALS:
        res = solve_ivp(func, (voi, output_point), states, args=(rates, constants, computed_constants, algebraic, externals, external_variable), method='LSODA', rtol=@RELATIVE_TOLERANCE@, atol=@ABSOLUTE_TOLERANCE@)
    else:
        res = solve_ivp(func, (voi, output_point), states, args=(rates, constants, computed_constants, algebraic), method='LSODA', rtol=@RELATIVE_TOLERANCE@, atol=@ABSOLUTE_TOLERANCE@)

    states = res.y[:, -1]

    voi = output_point

    # Compute our variables.

    if EXTERNALS:
        model.compute_variables(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable)
    else:
        model.compute_variables(voi, states, rates, constants, computed_constants, algebraic)

    # Output the value of our states, constants, computed constants, and algebraic variables.

    if EXTERNALS:
        print_values(file, voi, states, constants, computed_constants, algebraic, externals)
    else:
        print_values(file, voi, states, constants, computed_constants, algebraic)

file.close()
