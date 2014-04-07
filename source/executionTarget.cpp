#include "executionTarget.hpp"
#include "parseException.hpp"

#include <iostream>
#include <stdlib.h>

using namespace std;

ExecutionTarget::~ExecutionTarget()
{
}

int DefaultTarget::execute(ProgramConfiguration * configuration)
{
    PropositionalFormula * formula = NULL;
    int exit = EXIT_SUCCESS;

    while (true)
    {
        try
        {
            // Formula parsing
            formula = configuration->getParser()(*(configuration->getInput()));
            if (formula == NULL)
            {
                break;
            }

            // Formula printing
            if (configuration->getEcho())
            {
                cout << (formula->*configuration->getPrinter())
                        (configuration->getLanguage()) << endl;
            }
            delete formula;
        } catch (ParseException & exception)
        {
            // Parse error
            if (configuration->getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            exit = EXIT_FAILURE;
        }
    }
    return exit;
}

int AxiomCheck::execute(ProgramConfiguration * configuration)
{
    PropositionalFormula * formula = NULL;
    int exit = EXIT_SUCCESS;

    while (true)
    {
        try
        {
            // Formula parsing
            formula = configuration->getParser()(*(configuration->getInput()));
            if (formula == NULL)
            {
                break;
            }

            // Axiom validating
            int type;
            if ((type = system.validateAxiom(formula)) > 0)
            {
                if (configuration->getEcho())
                {
                    cout << "Type " << type << " axiom." << endl;
                }
            } else
            {
                if (configuration->getEcho())
                {
                    cout << "Not an axiom." << endl;
                }
                exit = EXIT_FAILURE;
            }
            delete formula;
        } catch (ParseException & exception)
        {
            // Parse error
            if (configuration->getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            exit = EXIT_FAILURE;
        }
    }
    return exit;
}

ProofCheck::~ProofCheck()
{
    for (PropositionalFormula * formula : validProof)
    {
        delete formula;
    }
}

int ProofCheck::execute(ProgramConfiguration * configuration)
{
    PropositionalFormula * formula;
    int exit = EXIT_SUCCESS;

    while (true)
    {
        try
        {
            // Formula parsing
            formula = configuration->getParser()(*(configuration->getInput()));
            if (formula == NULL)
            {
                break;
            }

            // Proof validating
            int type;
            string * message;
            if ((type = system.validateAxiom(formula)) > 0)
            {
                // Axiom validating
                if (configuration->getEcho())
                {
                    cout << "Provable being a type " << type << " axiom." << endl;
                }
                validProof.push_back(formula);
            } else
            {
                // Modus ponens proving
                message = system.proveFormula(formula, validProof);
                if (configuration->getEcho())
                {
                    cout << message << endl;
                }

                if (message != NULL)
                {
                    validProof.push_back(formula);
                    delete message;
                } else
                {
                    delete message;
                    delete formula;
                    exit = EXIT_FAILURE;
                    break;
                }
            }
        } catch (ParseException & exception)
        {
            // Parse exception
            if (configuration->getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            exit = EXIT_FAILURE;
            break;
        }
    }
    return exit;
}
