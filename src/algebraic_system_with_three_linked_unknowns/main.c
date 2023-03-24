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
                        "'x', 'y', and 'z' have an initial guess of 1.");

    // Compute our model by first computing our computed constants (in case
    // there are some) and then our variables.

    computeComputedConstants(variables);
    computeVariables(variables);

    // Output the final value of our model variables.

    printVariableValues("Final variable values", variables,
                        "'x', 'y', and 'z' should have a value of 1, -1, and 1, respectively.");

    // Clean up after ourselves.

    deleteArray(variables);

    return 0;
}
