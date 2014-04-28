#include "target.hpp"
#include "parseException.hpp"

#include <iostream>
#include <stdlib.h>

using namespace std;

Target::~Target()
{
}

int DefaultTarget::execute(Configuration * configuration)
{
    Formula * formula = NULL;
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
            if (configuration->getStrict())
            {
                break;
            }
        }
    }
    return exit;
}

int AxiomCheck::execute(Configuration * configuration)
{
    Formula * formula = NULL;
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
                if (configuration->getStrict())
                {
                    break;
                }
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
            if (configuration->getStrict())
            {
                break;
            }
        }
    }
    return exit;
}

ProofCheck::~ProofCheck()
{
    for (Formula * formula : validProof)
    {
        delete formula;
    }
}

bool ProofCheck::contains(Formula * formula) const
{
    for (Formula * proofFormula : validProof)
    {
        if (proofFormula->equals(formula)) return true;
    }
    return false;
}

int ProofCheck::execute(Configuration * configuration)
{
    Formula * formula;
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
            string * message = NULL;

            if (configuration->getSimplify() && contains(formula))
            {
                if (configuration->getEcho())
                {
                    cout << "The proof already contains this formula." << endl;
                }
                delete formula;
            } else if ((type = system.validateAxiom(formula)) > 0)
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
                    if (message != NULL)
                    {
                        cout << *message << endl;
                    } else
                    {
                        cout << "Inprovable within this proof." << endl;
                    }
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
