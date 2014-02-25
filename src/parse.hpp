#ifndef PARSE_HPP
#define	PARSE_HPP

#include <cstdio>
#include <map>

#include "connective.hpp"
#include "formula.hpp"

const std::map<const char, Connective> CONNECTIVES = {
    {'-', NEGATION},
    {'.', CONJUNCTION},
    {'+', DISJUNCTION},
    {'>', IMPLICATION},
    {'=', EQUIVALENCE}
};

Formula * parsePrefix(std::istream &);
Formula * parseInfix(std::istream &);
Formula * parsePostfix(std::istream &);

#endif	/* PARSE_HPP */

