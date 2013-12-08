#ifndef PARSER_HPP
#define	PARSER_HPP

#include <sstream>
#include <stack>
#include <string>

#include "formula.hpp"

class Parser
{
public:
    Formula * parseInPrefix(std::string) const;
    Formula * parseInInfix(std::string) const;
    Formula * parseInPostfix(std::string) const;
};

#endif	/* PARSER_HPP */

