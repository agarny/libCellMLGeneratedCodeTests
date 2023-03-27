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

    printVariableValues("Initial variable values/guesses", variables, {{"a", 1.0}, {"b", 3.0}, {"c", 5.0}, {"d", 7.0}});

    // Compute our variables.

    computeVariables(variables);

    // Output the final value of our model variables.

    printVariableValues("Final variable values", variables, {{"a", 9.0}, {"b", 3.0}, {"c", 5.0}, {"d", 7.0}});

    // Clean up after ourselves.

    deleteArray(variables);

    return 0;
}
