#include <cstdlib>
#include <iostream>

#include "formula.hpp"
#include "parse.hpp"

int main(int argc, char** argv)
{
    Formula * formula;

    const char * errorMessage = "Program syntax: <input format ... {0, 1, 2}> <output format ... {0, 1, 2}> <formula>";

    if (argc != 4)
    {
        std::cerr << errorMessage << std::endl;
        return 1;
    }

    switch (atoi(argv[1]))
    {
        case 0:
            formula = parsePrefix(std::string(argv[3]));
            break;
        case 1:
            formula = parseInfix(std::string(argv[3]));
            break;
        case 2:
            formula = parsePostfix(std::string(argv[3]));
            break;
        default:
            std::cerr << errorMessage << std::endl;
            return 1;
            break;
    }

    switch (atoi(argv[2]))
    {
        case 0:
            std::cout << formula->printPrefix() << std::endl;
            break;
        case 1:
            std::cout << formula->printInfix() << std::endl;
            break;
        case 2:
            std::cout << formula->printPostfix() << std::endl;
            break;
        default:
            std::cerr << errorMessage << std::endl;
            return 1;
            break;
    }

    return 0;
}

