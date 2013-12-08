#include <iostream>

#include "formula.hpp"
#include "parser.hpp"

int main(int argc, char** argv)
{
    std::string input;
    Parser parser;

    std::getline(std::cin, input);

    std::cout << parser.parseInInfix(input)->printInInfix() << std::endl;

    return 0;
}

