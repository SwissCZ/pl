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
    Formula * parsePrefix(std::string);
    Formula * parseInfix(std::string);
    Formula * parsePostfix(std::string);
};

#endif	/* PARSER_HPP */

