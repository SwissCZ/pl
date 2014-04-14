#ifndef CONFIGURATION_HPP
#define	CONFIGURATION_HPP

#include "formula.hpp"
#include "parse.hpp"

#include <fstream>
#include <iostream>

using namespace std;

class Target;

typedef Formula * (* Parser)(istream &); ///< Parse function pointer.
typedef string(Formula::* Printer) (Language) const; ///< Print method pointer.

//! Program configuration structure.

/**
 * Contains default initialized variables adjusting the program execution.
 */
class Configuration
{
private:
    static map<string, Parser> inputSyntax; ///< Input syntax values.
    static map<string, Printer> outputSyntax; ///< Output syntax values.
    static map<string, Language> outputLanguage; ///< Output language values.

    istream * input = &cin; ///< Input stream to read from.
    Parser parser = &parseInfix; ///< Input parser to use.
    Printer printer = &Formula::printInfix; ///< Output printer to use.
    Language language = ASCII; ///< Output language of connectives.
    Target * target = NULL; ///< Execution target to peform.
    bool echo = false; ///< Echo flag.
    bool strict = false; ///< Strict behavior flag.

    ifstream file; ///< File input stream to read from.
public:
    Configuration(int, char **);
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
     * Output printer getter.
     * @return Output printer to use.
     */
    Printer getPrinter() const;
    /**
     * Output lanugage getter.
     * @return Output language of connectives.
     */
    Language getLanguage() const;
    /**
     * Execution target getter.
     * @return Execution target to perform.
     */
    Target * getTarget() const;
    /**
     * Echo flag getter.
     * @return Echo flag.
     */
    bool getEcho() const;
    /**
     * Strict behavior flag getter.
     * @return Strict behavior flag.
     */
    bool getStrict() const;
};

#endif
