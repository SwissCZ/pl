#include "formula.hpp"
#include "hilbert.hpp"
#include "parseException.hpp"
#include "proof.hpp"
#include "target.hpp"

#include <iostream>
#include <list>

using namespace std;

int executeDefault(Configuration * configuration)
{
    Formula * formula = NULL;
    int exit = 0;

    while (true)
    {
        try
        {
            // Formula parsing
            formula = configuration->parse();
            if (formula == NULL)
            {
                break;
            }

            // Formula printing
            if (configuration->getEcho())
            {
                cout << configuration->print(formula) << endl;
            }
            delete formula;
        } catch (ParseException & exception)
        {
            exit = 1;
            if (configuration->getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            if (configuration->getStrict())
            {
                break;
            }
        }
    }
    return exit;
}

int executeAxiomCheck(Configuration * configuration)
{
    Formula * formula = NULL;
    int exit = 0;
    int type;

    while (true)
    {
        try
        {
            // Formula parsing
            formula = configuration->parse();
            if (formula == NULL)
            {
                break;
            }

            // Axiom checking
            type = hilbertSystem.isAxiom(formula);
            if (type > 0)
            {
                if (configuration->getEcho())
                {
                    cout << "Type " <<
                            type <<
                            " axiom." <<
                            endl;
                }
            } else
            {
                exit = 1;
                if (configuration->getEcho())
                {
                    cout << "Not an axiom." << endl;
                }
                if (configuration->getStrict())
                {
                    delete formula;
                    break;
                }
            }
            delete formula;
        } catch (ParseException & exception)
        {
            exit = 1;
            if (configuration->getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            if (configuration->getStrict())
            {
                break;
            }
        }
    }
    return exit;
}

int executeProofCheck(Configuration * configuration)
{
    Formula * formula;
    int exit = 0;
    Proof proof;
    int type;
    int * indexes;
    while (true)
    {
        try
        {
            // Formula parsing
            formula = configuration->parse();
            if (formula == NULL)
            {
                break;
            }

            // Proof simplification
            if (configuration->getSimplify() && proof.contains(formula))
            {
                if (configuration->getEcho())
                {
                    cout << "Already contained." << endl;
                }
                delete formula;
                continue;
            }

            // Axiom checking
            type = hilbertSystem.isAxiom(formula);
            if (type > 0)
            {
                proof.add(formula);
                if (configuration->getEcho())
                {
                    cout << "Type " <<
                            type <<
                            " axiom." <<
                            endl;
                }
                continue;
            }

            // Rules checking
            indexes = hilbertSystem.isProvable(formula, proof);
            if (indexes != NULL)
            {
                proof.add(formula);
                if (configuration->getEcho())
                {
                    cout << "Provable (modus ponens) "
                            "using formulas " <<
                            indexes[0] <<
                            " and " <<
                            indexes[1] <<
                            "." <<
                            endl;
                }
                delete indexes;
                continue;
            }

            // Formula is not provable.
            exit = 1;
            if (configuration->getStrict())
            {
                cout << "Not provable." << endl;
            }
            delete indexes;
            delete formula;
            break;
        } catch (ParseException & exception)
        {
            exit = 1;
            if (configuration->getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            break;
        }
    }
    return exit;
}
