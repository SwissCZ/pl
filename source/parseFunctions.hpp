#ifndef PARSE_FUNCTIONS_HPP
#define	PARSE_FUNCTIONS_HPP

#include "propositionalFormula.hpp"

#include <istream>

using namespace std;

//! Parse in prefix.

/**
 * Parses a formula written in prefix.
 * @param input Input stream to read from.
 * @return Formula expression tree root node.
 */
PropositionalFormula * parsePrefix(istream & input);

//! Parse in infix.

/**
 * Parses a formula written in infix.
 * @param input Input stream to read from.
 * @return Formula expression tree root node.
 */
PropositionalFormula * parseInfix(istream & input);

//! Parse in postfix.

/**
 * Parses a formula written in postfix.
 * @param input Input stream to read from.
 * @return Formula expression tree root node.
 */
PropositionalFormula * parsePostfix(istream & input);

#endif	/* PARSE_FUNCTIONS_HPP */
