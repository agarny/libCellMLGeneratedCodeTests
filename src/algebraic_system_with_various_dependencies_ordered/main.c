#include "algebraicmodel.h"
#include "common.h"
#include "model.h"

int main()
{
    // Some information about the model.

    printInformation();

    // Create the array of variables needed to compute the model.

    double *variables = createVariablesArray();

    // Initialise and output our model variables.

    initialiseVariables(variables);

    printVariableValues("Initial variable values/guesses", variables,
                        "'b' and 'c' have an initial guess of 1.");

    // Compute our model by first computing our computed constants (in case
    // there are some) and then our variables.

    computeComputedConstants(variables);
    computeVariables(variables);

    // Output and check the final value of our model variables.

    printVariableValues("Final variable values", variables,
                        "'a', 'b', 'b', 'd', 'x', and 'y' should have a value of 14, 4, 7, 11, 3, and 5, respectively.");

    // Clean up after ourselves.

    deleteArray(variables);

    return 0;
}
