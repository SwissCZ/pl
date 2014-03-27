#ifndef CONFIGURATION_HPP
#define	CONFIGURATION_HPP

#include "formula.hpp"
#include "language.hpp"
#include "parse.hpp"
#include "target.hpp"

#include <fstream>
#include <iostream>

using namespace std;

typedef Formula * (* parse)(istream &); ///< Parse function pointer
typedef string(Formula::* print) (Language) const; ///< Print method pointer

//! Program configuration

/**
 * Contains default-initialized variables directing the program execution.
 */
class Configuration
{
private:
    static map<string, parse> INPUT_NOTATION;
    //< Input notation optino values
    static map<string, print> OUTPUT_NOTATION;
    //< Output notation option values
    static map<string, Language> OUTPUT_LANGUAGE;
    //< Output language option values

    istream * inputStream = &cin; ///< Input stream to parse
    ifstream fileStream;
    parse parser = &parseInfix; ///< Input parser to use
    print printer = &Formula::printInfix; ///< Output printing method
    Language language = ASCII; ///< Output language of connectives
    Target * target = NULL; ///< Target to execute
    bool echo = false; ///< Whether to echo parsed formulas or not
public:

    /**
     * Parses the command line parameters and adjusts the configuration.
     * @param argc Command line parameters count
     * @param argv Command line parameters array
     */
    Configuration(int argc, char ** argv);
    ~Configuration();
    /**
     * Input stream getter.
     * @return Input stream to parse
     */
    istream * getInput() const;
    /**
     * Parsing function getter.
     * @return Input parser to use
     */
    parse getParser() const;
    /**
     * Printing mehod getter.
     * @return Output printing method
     */
    print getPrinter() const;
    /**
     * Lanugage getter.
     * @return Output language of connectives
     */
    Language getLanguage() const;
    /**
     * Target instance getter.
     * @return Target to execute
     */
    Target * getTarget() const;
    /**
     * Echo flag getter.
     * @return Whether to echo parsed formulas or not
     */
    bool getEcho() const;
};

#endif	/* CONFIGURATION_HPP */
