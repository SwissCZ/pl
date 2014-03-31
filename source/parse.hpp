#ifndef PARSE_HPP
#define	PARSE_HPP

#include "formula.hpp"

#include <istream>

using namespace std;

/**
 * Parses formula in prefix notation.
 * @param input Input stream to read from.
 * @return Formula expression tree root node.
 */
Formula * parsePrefix(istream & input);
/**
 * Parses formula in infix notation.
 * @param input Input stream to read from.
 * @return Formula expression tree root node.
 */
Formula * parseInfix(istream & input);
/**
 * Parses formula in postfix notation.
 * @param input Input stream to read from.
 * @return Formula expression tree root node.
 */
Formula * parsePostfix(istream & input);

#endif	/* PARSE_HPP */
