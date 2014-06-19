#ifndef CONFIGURATION_HPP
#define	CONFIGURATION_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "formula.hpp"
#include "parseFormula.hpp"
#include "proofSystem.hpp"

using namespace std;

class ExecutionTarget;

typedef Formula* (*Parser)(istream&);
///< Formula parse function pointer

typedef string(Formula::*Printer)(Language) const;
///< Formula print method pointer

//! Program configuration structure

/**
 * Contains variables directing the program execution.
 */
class Configuration
{
private:
    static map<string, Parser> inputSyntaxes;
    ///< Input syntax values

    static map<string, Printer> outputSyntaxes;
    ///< Output syntax values

    static map<string, Language> outputLanguages;
    ///< Output language values

    ExecutionTarget* target = NULL;
    ///< Execution target to peform

    ProofSystem* system = NULL;
    ///< Proof system to operate within

    bool echo = false;
    ///< Echo flag

    bool strict = false;
    ///< Strict behaviour flag

    istream* input = &cin;
    ///< Input stream to read from

    ifstream file;
    ///< File input stream to read from

    Parser parser = &parseInfix;
    ///< Formula parser to use

    Printer printer = &Formula::printInfix;
    ///< Formula printer to use

    Language language = ASCII;
    ///< Output language of connectives to use
public:
    Configuration(int,
                  char**);
    ~Configuration();

    /**
     * Execution target getter.
     * @return Execution target to perform
     */
    ExecutionTarget* getTarget() const;

    /**
     * Proof system getter.
     * @return Proof system to operate within
     */
    ProofSystem* getSystem() const;

    /**
     * Echo flag getter.
     * @return Echo flag
     */
    bool getEcho() const;

    /**
     * Strict behaviour flag getter.
     * @return Strict behaviour flag
     */
    bool getStrict() const;

    /**
     * Parses a formula.
     * @return Formula expression tree root node
     */
    Formula* parseFormula() const;

    /**
     * Returns a textual representation of given formula.
     * @param formula Formula to be printed
     * @return Textual representation of given formula
     */
    string printFormula(Formula* formula) const;
};

#endif
