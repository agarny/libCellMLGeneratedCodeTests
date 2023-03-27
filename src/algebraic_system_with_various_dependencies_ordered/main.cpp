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

    printVariableValues("Initial variable values/guesses", variables, {{"a", 14.0}, {"b", 1.0}, {"c", 1.0}, {"d", 0.0}, {"x", 3.0}, {"y", 5.0}});

    // Compute our variables.

    computeVariables(variables);

    // Output the final value of our model variables.

    printVariableValues("Final variable values", variables, {{"a", 14.0}, {"b", 4.0}, {"c", 7.0}, {"d", 11.0}, {"x", 3.0}, {"y", 5.0}});

    // Clean up after ourselves.

    deleteArray(variables);

    return 0;
}
