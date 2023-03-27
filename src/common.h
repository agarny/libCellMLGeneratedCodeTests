#include <map>
#include <string>

extern "C" {
void nlaSolve(void (*objectiveFunction)(double *, double *, void *), double *u, int n, void *data);
}

bool areNearlyEqual(double a, double b);

int iwidth(double n);
