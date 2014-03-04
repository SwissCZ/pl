#ifndef CONFIGURATION_HPP
#define	CONFIGURATION_HPP

#include <iostream>

#include "formula.hpp"
#include "language.hpp"
#include "parse.hpp"

using namespace std;

/**
 * Program targets. Indicates the available targets of the program.
 */
enum Target
{
    DEFAULT ///< Parse input & report errors
};

/**
 * Program configuration. Structure containing default-initialized variables
 * adjusting the program execution.
 */
struct Configuration
{
    Formula * (* parse)(istream &) = &parseInfix; ///< Expected input notation
    string(Formula::* print) (Language) const = &Formula::printPrefix;
    ///< Output formulas notation
    Language outputLanguage = ASCII; ///< Output formulas language
    Target target = DEFAULT; ///< Target to be performed
    istream * inputStream = &cin; ///< Input stream to be parsed

    /**
     * Parses the command line parameters and configures the program.
     * @param argc Command line parameters count
     * @param argv Command line parameters array
     */
    Configuration(int argc, char ** argv);
    ~Configuration();
};

#endif	/* CONFIGURATION_HPP */
