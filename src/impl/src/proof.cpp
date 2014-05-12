#include "proof.hpp"

using namespace std;

Proof::~Proof()
{
    for (Formula * formula : formulas)
    {
        delete formula;
    }
}

const list<Formula *> & Proof::getFormulas() const
{
    return formulas;
}

bool Proof::contains(Formula * formula) const
{
    for (Formula * proofFormula : formulas)
    {
        if (proofFormula->equals(formula))
        {
            return true;
        }
    }
    return false;
}

void Proof::add(Formula * formula)
{
    formulas.push_back(formula);
}
