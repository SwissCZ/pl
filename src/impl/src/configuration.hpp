#ifndef CONFIGURATION_HPP
#define	CONFIGURATION_HPP

#include <fstream>
#include <iostream>

#include "formula.hpp"
#include "parse.hpp"

using namespace std;

class Configuration;

typedef Formula * (* Parser)(istream &); ///< Parse function pointer.
typedef int (* Target)(Configuration *); ///< Execution target function pointer.
typedef string(Formula::* Printer) (Language) const; ///< Print method pointer.

//! Program configuration structure.

/**
 * Contains default initialized variables adjusting the program execution.
 */
class Configuration
{
private:
    static const map<string, Parser> inputSyntax; ///< Input syntax values.
    static const map<string, Printer> outputSyntax; ///< Output syntax values.
    static const map<string, Language> outputLanguage; ///< Output language values.

    istream * input = &cin; ///< Input stream to read from.
    Parser parser = &parseInfix; ///< Formula parser to use.
    Printer printer = &Formula::printInfix; ///< Output printer to use.
    Target target = NULL; ///< Execution target to peform.
    Language language = ASCII; ///< Output language of connectives.
    bool echo = false; ///< Echo flag.
    bool strict = false; ///< Strict behavior flag.
    bool simplify = false; ///< Proof simplification flag.

    ifstream file; ///< File input stream to read from.
public:
    Configuration(int, char **);
    ~Configuration();
    /**
     * Parses formula in set syntax.
     * @return Formula expression tree root node.
     */
    Formula * parse() const;
    /**
     * Returns a textual representation of given formula in set syntax.
     * @param formula Formula to be printed.
     * @return Textual representation of given formula.
     */
    string print(Formula * formula) const;
    /**
     * Execution target getter.
     * @return Execution target to perform.
     */
    Target getTarget() const;
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
    /**
     * Proof simplification flag getter.
     * @return Proof simplification flag.
     */
    bool getSimplify() const;
};

#endif
