#ifndef PARSE_HPP
#define	PARSE_HPP

#include <cstdio>

#include "formula.hpp"

Formula * parsePrefix(std::istream &);
Formula * parseInfix(std::istream &);
Formula * parsePostfix(std::istream &);

#endif	/* PARSE_HPP */

