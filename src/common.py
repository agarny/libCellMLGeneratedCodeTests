import math
from scipy.optimize import fsolve


def nla_solve(objective_function, u, n, data):
    def func(u):
        f = [0.0] * n

        objective_function(u, f, data)

        return f

    return fsolve(func, u)


def iwidth(n):
    if math.isclose(n, 0.0):
        return 1

    return int(int(n < 0.0) + math.log10(math.fabs(round(n))) + 1)
