import math


def nla_solve(objective_function, u, n, data):
    pass

def iwidth(n):
    if math.isclose(n, 0.0):
        return 1

    return int(int(n < 0.0) + math.log10(math.fabs(math.trunc(n))) + 1)
