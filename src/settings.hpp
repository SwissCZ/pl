#ifndef SETTINGS_HPP
#define	SETTINGS_HPP

#include <iostream>

#include "language.hpp"
#include "notation.hpp"
#include "target.hpp"

using namespace std;

/**
 * Program configuration structure.
 */
struct Configuration
{
    Notation inputNotation = INFIX; ///< Expected input notion
    Notation outputNotation = INFIX; ///< Output formulas notation
    Language outputLanguage = ASCII; ///< Output formulas language
    Target target = DEFAULT; ///< Target to be performed
    istream * inputStream = &cin; ///< Input stream to be read from

    Configuration(int argc, char ** argv);
    ~Configuration();
};

#endif	/* SETTINGS_HPP */
