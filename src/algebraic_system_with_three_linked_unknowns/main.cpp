#include "algebraicmodel.h"
#include "common.h"

extern "C" {
#include "model.h"
}

int main()
{
    // Some information about the model.

    printInformation();

    // Create the array of variables needed to compute the model.

    double *variables = createVariablesArray();

    // Initialise our variables, compute our computed constants, and output our model variables.

    initialiseVariables(variables);
    computeComputedConstants(variables);

    printVariableValues("Initial variable values/guesses", variables, {{"x", 1.0}, {"y", 1.0}, {"z", 1.0}});

    // Compute our variables.

    computeVariables(variables);

    // Output the final value of our model variables.

    printVariableValues("Final variable values", variables, {{"x", 1.0}, {"y", -1.0}, {"z", 1.0}});

    // Clean up after ourselves.

    deleteArray(variables);

    return 0;
}
