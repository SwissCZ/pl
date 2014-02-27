#ifndef PARSE_HPP
#define	PARSE_HPP

#include <cstdio>
#include <map>

#include "formula.hpp"
#include "operation.hpp"

using namespace std;

const map<const char, Operation> connectiveMap = {
    {'-', NEGATION},
    {'.', CONJUNCTION},
    {'+', DISJUNCTION},
    {'>', IMPLICATION},
    {'=', EQUIVALENCE}
}; ///< Input language definition

/**
 * Parses a formula in prefix notation into an expression tree.
 * @param input Input stream to be parsed
 * @return Formula expression tree root node
 */
Formula * parsePrefix(istream & input);
/**
 * Parses a formula in infix notation into an expression tree.
 * @param input Input stream to be parsed
 * @return Formula expression tree root node
 */
Formula * parseInfix(istream & input);
/**
 * Parses a formula in postfix notation into an expression tree.
 * @param input Input stream to be parsed
 * @return Formula expression tree root node
 */
Formula * parsePostfix(istream & input);

#endif	/* PARSE_HPP */
