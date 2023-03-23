#include "algebraicmodel.h"

#include <stdio.h>

char * variableType(VariableType variableType)
{
    char *res;

    switch (variableType) {
    case CONSTANT:
        res = "constant";

        break;
    case COMPUTED_CONSTANT:
        res = "computed constant";

        break;
    default: // ALGEBRAIC.
        res = "algebraic";

        break;
    }

    return res;
}

void printInformation()
{
    printf("---------------------------------------[Information][BEGIN]\n");
    printf("- Generator version: %s\n", VERSION);
    printf("- libCellML version: %s\n", LIBCELLML_VERSION);
    printf("---------------------------------------\n");
    printf("- Number of variables: %lu\n", VARIABLE_COUNT);
    printf("- Variables:\n");

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        printf("   - %s [%s]:\n", VARIABLE_INFO[i].name, VARIABLE_INFO[i].units);
        printf("      - Type: %s\n", variableType(VARIABLE_INFO[i].type));
        printf("      - Component: %s\n", VARIABLE_INFO[i].component);
    }

    printf("---------------------------------------[Information][END]\n");
}
