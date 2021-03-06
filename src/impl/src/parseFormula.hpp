#ifndef PARSE_FORMULA_HPP
#define	PARSE_FORMULA_HPP

#include <istream>

#include "formula.hpp"

using namespace std;

//! Parse formula in prefix

/**
 * Parses a formula in prefix syntax.
 * @param input Input stream to read from
 * @return Formula expression tree root node
 */
Formula* parsePrefix(istream& input);

//! Parse formula in infix

/**
 * Parses a formula in infix syntax.
 * @param input Input stream to read from
 * @return Formula expression tree root node
 */
Formula* parseInfix(istream& input);

//! Parse formula in postfix

/**
 * Parses a formula in postfix syntax.
 * @param input Input stream to read from
 * @return Formula expression tree root node
 */
Formula* parsePostfix(istream& input);

#endif
