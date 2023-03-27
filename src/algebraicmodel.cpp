#include "algebraicmodel.h"

std::string variableType(VariableType variableType)
{
    std::string res;

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
    std::cout << "---------------------------------------[Information][BEGIN]" << std::endl;
    std::cout << "- Generator version: " << VERSION << std::endl;
    std::cout << "- libCellML version: " << LIBCELLML_VERSION << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "- Number of variables: " << VARIABLE_COUNT << std::endl;
    std::cout << "- Variables:" << std::endl;

    for (size_t i = 0; i < VARIABLE_COUNT; ++i) {
        std::cout << "   - " << VARIABLE_INFO[i].name << " [" << VARIABLE_INFO[i].units << "]:" << std::endl;
        std::cout << "      - Type: " << variableType(VARIABLE_INFO[i].type) << std::endl;
        std::cout << "      - Component: " << VARIABLE_INFO[i].component << std::endl;
    }

    std::cout << "---------------------------------------[Information][END]" << std::endl;
}
