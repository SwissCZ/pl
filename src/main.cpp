#include <cstdlib>
#include <exception>
#include <iostream>

#include "formula.hpp"
#include "parse.hpp"

int main(int argc, char** argv)
{
    Formula * formula;

    while (true)
    {
        try
        {
            // Input
            switch (atoi(argv[1]))
            {
                case 0:
                    formula = parsePrefix(std::cin);
                    break;
                case 1:
                    formula = parseInfix(std::cin);
                    break;
                case 2:
                    formula = parsePostfix(std::cin);
                    break;
                default:
                    std::cout << "Re-run with a valid syntax." << std::endl;
                    break;
            }

            // EOF check
            if (formula == NULL)
            {
                break;
            };

            // Output
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
                    std::cout << "Re-run with a valid syntax." << std::endl;
                    break;
            }

            delete formula;
        } catch (std::exception & ex)
        {
            std::cerr << ex.what() << std::endl;
        }
    }

    return 0;
}

