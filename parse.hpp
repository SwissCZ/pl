#ifndef PARSE_HPP
#define	PARSE_HPP

#include <string>

#include "formula.hpp"

Formula * parsePrefix(std::string);
Formula * parseInfix(std::string);
Formula * parsePostfix(std::string);

#endif	/* PARSE_HPP */

