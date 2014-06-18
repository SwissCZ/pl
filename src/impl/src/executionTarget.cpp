#include <iostream>
#include <list>

#include "executionTarget.hpp"
#include "formula.hpp"
#include "parseException.hpp"
#include "proofSystem.hpp"

ExecutionTarget::~ExecutionTarget()
{
}

int DefaultTarget::execute(Configuration& configuration) const
{
    Formula* formula = NULL;
    int exit = 0;

    while (true)
    {
        try
        {
            formula = configuration.parseFormula();
            if (formula == NULL)
            {
                break;
            }
            if (configuration.getEcho())
            {
                cout << configuration.printFormula(formula) << endl;
            }
            delete formula;
        } catch (ParseException& exception)
        {
            exit = 1;
            if (configuration.getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            if (configuration.getStrict())
            {
                break;
            }
        }
    }
    return exit;
}

int AxiomChecker::execute(Configuration& configuration) const
{
    Formula* formula = NULL;
    int exit = 0;
    int type;

    while (true)
    {
        try
        {
            formula = configuration.parseFormula();
            if (formula == NULL)
            {
                break;
            }
            type = configuration.getSystem()->isAxiom(formula);
            if (type > 0)
            {
                if (configuration.getEcho())
                {
                    cout << "Axiom of type " << type << "." << endl;
                }
            } else
            {
                exit = 1;
                if (configuration.getEcho())
                {
                    cout << "Not an axiom." << endl;
                }
                if (configuration.getStrict())
                {
                    delete formula;
                    break;
                }
            }
            delete formula;
        } catch (ParseException& exception)
        {
            exit = 1;
            if (configuration.getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            if (configuration.getStrict())
            {
                break;
            }
        }
    }
    return exit;
}

ProofHandler::ProofHandler(int premises,
                           bool optimize)
{
    this->premises = premises;
    this->optimize = optimize;
}

int ProofHandler::execute(Configuration& configuration) const
{
    int exit = 0;
    int premisesCount = premises;
    unsigned type;
    Formula* formula;
    list<Formula*> theory;
    vector<ProofElement> proof;
    list<int> indexes;

    while (true)
    {
        try
        {
            // Formula parsing
            formula = configuration.parseFormula();
            if (formula == NULL)
            {
                break;
            }

            // Premises storing
            if (premisesCount)
            {
                theory.push_back(formula);
                premisesCount--;
            }

            // Axiom checking
            type = configuration.getSystem()->isAxiom(formula);
            if (type > 0)
            {
                proof.push_back(ProofElement(formula));
                if (configuration.getEcho())
                {
                    cout << "Axiom of type " << type << "." << endl;
                }
                continue;
            }

            // Premise checking
            type = 1;
            for (Formula* premise: theory)
            {
                if (formula->equals(premise))
                {
                    if (configuration.getEcho())
                    {
                        cout << "Premise of type " << type << "." << endl;
                        break;
                    }
                }
                type++;
            }
            if (type <= theory.size())
            {
                continue;
            }

            // Rules checking
            indexes = configuration.getSystem()->isDeducible(formula, proof);
            if (!indexes.empty())
            {
                list<ProofElement*> witnesses;
                for (int index: indexes)
                {
                    witnesses.push_back(&proof[index]);
                }
                proof.push_back(ProofElement(formula, witnesses));
                if (configuration.getEcho())
                {
                    cout << "Provable using formulas ";
                    for (int index: indexes)
                    {
                        cout << index << " ";
                    }
                    cout << "as witnesses." << endl;
                }
                continue;
            }

            // Formula is not provable.
            if (configuration.getEcho())
            {
                cout << "Not provable." << endl;
            }
            delete formula;
            break;
        } catch (ParseException& exception)
        {
            exit = 1;
            if (configuration.getEcho())
            {
                cerr << exception.getMessage() << endl;
            }
            break;
        }
    }

    // Proof optimization
    if (optimize)
    {
        list<ProofElement*> queue;
        unsigned preserved = 0;

        queue.push_back(&proof.back());
        while (!queue.empty())
        {
            for (ProofElement* witness: queue.front()->getWitnesses())
            {
                queue.push_back(witness);
            }
            queue.front()->setPreserve(true);
            preserved++;
        }
        if (preserved == proof.size())
        {
            cerr << "Already optimal." << endl;
            exit = 1;
        } else
        {
            for (ProofElement element: proof)
            {
                cout << configuration.printFormula(element.getFormula()) << endl;
            }
        }
    }
    return exit;
}
