#include "model.h"

#include <kinsol/kinsol.h>
#include <nvector/nvector_serial.h>
#include <sunlinsol/sunlinsol_dense.h>

#include <stdio.h>

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

void printVariableValues(char *title, double *variables, char *note)
{
    printf("\n---------------------------------------[%s][BEGIN]\n", title);

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        printf("- %s: %f [%s]\n", VARIABLE_INFO[i].name, variables[i], VARIABLE_INFO[i].units);
    }

    printf("---------------------------------------\n");
    printf("Note: %s\n", note);
    printf("---------------------------------------[%s][END]\n", title);
}
