#ifndef PARSER_HPP
#define	PARSER_HPP

#include <string>

#include "formula.hpp"
#include "notation.hpp"

class Parser
{
public:
    Node * parse(std::string, Notation) const;
};

#endif	/* PARSER_HPP */

