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
} UserNlaData;

int func(N_Vector y, N_Vector f, void *userData)
{
    UserNlaData *realUserData = (UserNlaData *) userData;

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

    UserNlaData userData = { objectiveFunction, data };

    KINSetUserData(solver, &userData);

    // Set our maximum number of steps.

    KINSetMaxNewtonStep(solver, 9999999);

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
    if (isnan(a) && isnan(b)) {
        return true;
    }

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

    if (isnan(n)) {
        return 3;
    }

    return int(n < 0.0) + log10(fabs(round(n))) + 1;
}
