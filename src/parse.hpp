#ifndef PARSE_HPP
#define	PARSE_HPP

#include <cstdio>
#include <map>

#include "connective.hpp"
#include "formula.hpp"

using namespace std;

const map<const char, Connective> connective_map = {
    {'-', NEGATION},
    {'.', CONJUNCTION},
    {'+', DISJUNCTION},
    {'>', IMPLICATION},
    {'=', EQUIVALENCE}
};

Formula * parsePrefix(istream &);
Formula * parseInfix(istream &);
Formula * parsePostfix(istream &);

#endif	/* PARSE_HPP */
