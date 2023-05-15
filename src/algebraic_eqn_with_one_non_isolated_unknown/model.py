# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.4.0"

VARIABLE_COUNT = 4


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2


VARIABLE_INFO = [
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [0.0]*VARIABLE_COUNT


from common import nla_solve


def objective_function_0(u, f, data):
    variables = data[0]

    variables[3] = u[0]

    f[0] = variables[3]+variables[0]-(variables[1]+variables[2])


def find_root_0(variables):
    u = [0.0]*1

    u[0] = variables[3]

    nla_solve(objective_function_0, u, 1, (variables))

    variables[3] = u[0]


def initialise_variables(variables):
    variables[3] = 1.0
    variables[0] = 3.0
    variables[1] = 5.0
    variables[2] = 7.0


def compute_computed_constants(variables):
    pass


def compute_variables(variables):
    find_root_0(variables)
