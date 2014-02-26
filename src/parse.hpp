#ifndef PARSE_HPP
#define	PARSE_HPP

#include <cstdio>
#include <map>

#include "operation.hpp"
#include "formula.hpp"

using namespace std;

const map<const char, Operation> connective_map = {
    {'-', NEGATION},
    {'.', CONJUNCTION},
    {'+', DISJUNCTION},
    {'>', IMPLICATION},
    {'=', EQUIVALENCE}
}; ///< Input language definition

/**
 * Parses a formula in prefix notation into an expression tree.
 * @param Input stream to read from
 * @return Expression tree root node
 */
Formula * parsePrefix(istream &);
/**
 * The same as parsePrefix but infix notation is used.
 * @param Input stream to read from
 * @return Expression tree root node
 */
Formula * parseInfix(istream &);
/**
 * The same as parsePrefix but postfix notation is used.
 * @param Input stream to read from
 * @return Expression tree root node
 */
Formula * parsePostfix(istream &);

#endif	/* PARSE_HPP */
