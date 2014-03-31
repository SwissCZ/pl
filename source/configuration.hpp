#ifndef CONFIGURATION_HPP
#define	CONFIGURATION_HPP

#include "formula.hpp"
#include "parse.hpp"

#include <fstream>
#include <iostream>

using namespace std;

// Forward declaration of Target class to prevent circular dependency issue.
class Target;

// Type definitions for simplification purposes.
typedef Formula * (* Parser)(istream &); ///< Parse function pointer.
typedef string(Formula::* Printer) (Language) const; ///< Print method pointer.

//! Program configuration.

/**
 * Directs program execution.
 */
class Configuration
{
private:
    static map<string, Parser> inputNotation;
    ///< Input notation option values.
    static map<string, Printer> outputNotation;
    ///< Output notation option values.
    static map<string, Language> outputLanguage;
    ///< Output language option values.
    istream * inputStream = &cin; ///< Input stream to read from.
    ifstream fileStream; ///< File input stream to read from.
    Parser parser = &parseInfix; ///< Input parser to use.
    Printer printer = &Formula::printInfix; ///< Output print method to use.
    Language language = ASCII; ///< Output language of connectives.
    Target * target = NULL; ///< Program target to execute.
    bool echo = false; ///< To print textual reports or not.
public:
    Configuration(int argc, char ** argv);
    ~Configuration();
    /**
     * Input stream getter.
     * @return Input stream to read from.
     */
    istream * getInput() const;
    /**
     * Parse function getter.
     * @return Input parser to use.
     */
    Parser getParser() const;
    /**
     * Print mehod getter.
     * @return Output print method to use.
     */
    Printer getPrinter() const;
    /**
     * Lanugage getter.
     * @return Output language of connectives.
     */
    Language getLanguage() const;
    /**
     * Program target getter.
     * @return Program target to execute.
     */
    Target * getTarget() const;
    /**
     * Echo flag getter.
     * @return To print textual reports or not.
     */
    bool getEcho() const;
};

#endif	/* CONFIGURATION_HPP */
