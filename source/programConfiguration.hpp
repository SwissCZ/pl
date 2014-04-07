#ifndef PROGRAM_CONFIGURATION_HPP
#define	PROGRAM_CONFIGURATION_HPP

#include "parseFunctions.hpp"
#include "propositionalFormula.hpp"

#include <fstream>
#include <iostream>

using namespace std;

// Forward declaration of Target class to prevent circular dependency issue.
class ExecutionTarget;

// Type definitions for simplification purposes.
typedef PropositionalFormula * (* Parser)(istream &); ///< Parse function pointer.
typedef string(PropositionalFormula::* Printer) (Language) const; ///< Print method pointer.

//! Program configuration structure.

/**
 * Directs program execution.
 */
class ProgramConfiguration
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
    Printer printer = &PropositionalFormula::printInfix;
    ///< Output print method to use.
    Language language = ASCII; ///< Output language of connectives.
    ExecutionTarget * target = NULL; ///< Program target to execute.
    bool echo = false; ///< To print textual reports or not.
public:
    ProgramConfiguration(int argc, char ** argv);
    ~ProgramConfiguration();
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
    ExecutionTarget * getTarget() const;
    /**
     * Echo flag getter.
     * @return To print textual reports or not.
     */
    bool getEcho() const;
};

#endif	/* PROGRAM_CONFIGURATION_HPP */
