#include "common.h"

extern "C" {
#include "model.h"
}

#include <kinsol/kinsol.h>
#include <nvector/nvector_serial.h>
#include <sunlinsol/sunlinsol_dense.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

typedef struct {
    void (*objectiveFunction)(double *, double *, void *);
    void *data;
} UserData;

int func(N_Vector y, N_Vector f, void *userData)
{
    UserData *realUserData = (UserData *) userData;

    realUserData->objectiveFunction(N_VGetArrayPointer_Serial(y), N_VGetArrayPointer_Serial(f), realUserData->data);

    return 0;
}

void nlaSolve(void (*objectiveFunction)(double *, double *, void *), double *u, int n, void *data)
{
    // Create our SUNDIALS context.

    SUNContext context;

    SUNContext_Create(NULL, &context);

    // Create our KINSOL solver.

    void *solver = KINCreate(context);

    // Initialise our KINSOL solver.

    N_Vector y = N_VMake_Serial(n, u, context);

    KINInit(solver, func, y);

    // Set our user data.

    UserData userData = { objectiveFunction, data };

    KINSetUserData(solver, &userData);

    // Set our linear solver.

    SUNMatrix matrix = SUNDenseMatrix(n, n, context);
    SUNLinearSolver linearSolver = SUNLinSol_Dense(y, matrix, context);

    KINSetLinearSolver(solver, linearSolver, matrix);

    // Solve our linear system.

    N_Vector scale = N_VNew_Serial(n, context);

    N_VConst(1.0, scale);

    KINSol(solver, y, KIN_LINESEARCH, scale, scale);

    // Clean up after ourselves.

    N_VDestroy(scale);
    SUNLinSolFree(linearSolver);
    SUNMatDestroy(matrix);
    N_VDestroy_Serial(y);
    KINFree(&solver);
    SUNContext_Free(&context);
}

uint64_t ulpsDistance(double a, double b)
{
    if (std::isnan(a) || std::isnan(b)) {
        return UINT64_MAX;
    }

    if (std::isinf(a) != std::isinf(b)) {
        return UINT64_MAX;
    }

    static const int SIZE_OF_DOUBLE = sizeof(double);

    uint64_t ia;
    uint64_t ib;

    memcpy(&ia, &a, SIZE_OF_DOUBLE);
    memcpy(&ib, &b, SIZE_OF_DOUBLE);

    if (ia < ib) {
        return ib + ~ia + 1;
    }

    return ia + ~ib + 1;
}

bool areNearlyEqual(double a, double b)
{
    static const double EPSILON = std::numeric_limits<double>::epsilon();
    static const ptrdiff_t ULPS_EPSILON = 1;

    if (fabs(a - b) <= EPSILON) {
        return true;
    }

    if ((a < 0.0) != (b < 0.0)) {
        return false;
    }

    return ulpsDistance(a, b) <= ULPS_EPSILON;
}

int iwidth(double n)
{
    if (areNearlyEqual(n, 0.0)) {
        return 1;
    }

    return int(n < 0.0) + log10(fabs(trunc(n))) + 1;
}

void printVariableValues(const std::string &title, const double *variables, const std::map<std::string, double> &expectedValues)
{
    int w = 0;

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        auto cw = iwidth(variables[i]);

        if (cw > w) {
            w = cw;
        }
    }

    int ew = 0;
    auto ev = expectedValues.begin();

    for (size_t i = 0; i < expectedValues.size(); ++i) {
        auto ecw = iwidth((*ev).second);

        if (ecw > ew) {
            ew = ecw;
        }

        ++ev;
    }

    std::cout << std::endl << "---------------------------------------[" << title << "][BEGIN]" << std::endl;

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        std::printf("- %s: %s%.3f [%s]", VARIABLE_INFO[i].name, std::string(w - iwidth(variables[i]), ' ').c_str(), variables[i], VARIABLE_INFO[i].units);

        auto expectedValue = expectedValues.find(VARIABLE_INFO[i].name);

        if (expectedValue != expectedValues.end()) {
            if (areNearlyEqual(variables[i], expectedValue->second)) {
                std::cout << " |  OK";
            } else {
                std::printf(" | NOK | %s%.3f", std::string(ew - iwidth(expectedValue->second), ' ').c_str(), expectedValue->second);
            }
        }

        std::cout << std::endl;
    }

    std::cout << "---------------------------------------[" << title << "][END]" << std::endl;
}
