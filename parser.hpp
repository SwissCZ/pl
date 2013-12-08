#ifndef PARSER_HPP
#define	PARSER_HPP

#include <stack>
#include <string>
#include <sstream>

#include "formula.hpp"

class Parser
{
private:
    std::stringstream stream;
    std::stack<Formula *> stack;
    char buffer;
public:
    Formula * parseInPrefix(std::string);
    Formula * parseInInfix(std::string);
    Formula * parseInPostfix(std::string);
};

#endif	/* PARSER_HPP */

