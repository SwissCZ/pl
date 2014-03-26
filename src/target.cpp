#include "target.hpp"

#include <iostream>

using namespace std;

HilbertSystem Target::system;

Target::~Target()
{
}

bool Target::next(Formula * formula)
{
    delete formula;
    return true;
}

bool AxiomChecker::next(Formula * formula)
{
    int type;

    if ((type = system.validateAxiom(formula)))
    {
        cout << "Type " << type << " axiom." << endl;
    } else
    {
        cout << "Not an axiom." << endl;
    }
    return true;
}

bool ProofChecker::next(Formula * formula)
{
    int type;
    Provability * result;

    if ((type = system.validateAxiom(formula)))
    {
        cout << "Provable being a type " << type << " axiom." << endl;
    } else
    {
        result = system.validateModusPonens(formula, proof);
        cout << result->getMessage() << endl;

        if (!result->getProvability())
        {
            delete formula;
            return false;
        }
    }

    proof.push_back(formula);
    return true;
}
