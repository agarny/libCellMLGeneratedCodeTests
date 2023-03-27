#include <iostream>

extern "C" {
void nlaSolve(void (*objectiveFunction)(double *, double *, void *), double *u, int n, void *data);
}

void printVariableValues(const std::string &title, const double *variables, const std::string &note);
