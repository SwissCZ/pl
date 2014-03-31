#include "target.hpp"
#include "parseException.hpp"

#include <iostream>
#include <stdlib.h>

using namespace std;

HilbertSystem Target::system;

Target::~Target()
{
}

int Target::perform(Configuration * configuration)
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
                cerr << exception.what() << endl;
            }
            exit = EXIT_FAILURE;
        }
    }
    return exit;
}

int AxiomChecker::perform(Configuration * configuration)
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
            }
            delete formula;
        } catch (ParseException & exception)
        {
            // Parse error
            if (configuration->getEcho())
            {
                cerr << exception.what() << endl;
            }
            exit = EXIT_FAILURE;
        }
    }
    return exit;
}

ProofChecker::~ProofChecker()
{
    for (Formula * formula : proof)
    {
        delete formula;
    }
}

int ProofChecker::perform(Configuration * configuration)
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
            Provability * provability;

            if ((type = system.validateAxiom(formula)) > 0)
            {
                // Axiom validating
                if (configuration->getEcho())
                {
                    cout << "Provable being a type " << type << " axiom." << endl;
                }
                proof.push_back(formula);
            } else
            {
                // Modus ponens proving
                provability = system.validateModusPonens(formula, proof);
                if (configuration->getEcho())
                {
                    cout << provability->getMessage() << endl;
                }

                if (provability->getProvability())
                {
                    proof.push_back(formula);
                } else
                {
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
                cerr << exception.what() << endl;
            }
            exit = EXIT_FAILURE;
            break;
        }
    }
    return exit;
}
