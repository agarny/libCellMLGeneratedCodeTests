import math
from scipy.optimize import fsolve


def nla_solve(objective_function, u, n, data):
    def func(u):
        f = [math.nan] * n

        objective_function(u, f, data)

        return f

    return fsolve(func, u)


def area_nearly_equal(a, b):
    return math.isclose(a, b) or (math.isnan(a) and math.isnan(b))


def iwidth(n):
    if area_nearly_equal(n, 0.0):
        return 1

    if math.isnan(n):
        return 3

    return int(int(n < 0.0) + math.log10(math.fabs(round(n))) + 1)
