#include <sstream>

#include "parseFormula.hpp"
#include "proofSystem.hpp"

ProofSystem::ProofSystem(list<string> axiomStrings)
{
    stringstream stream;

    for (string axiomString: axiomStrings)
    {
        stream << axiomString << endl;
        axioms.push_back(parseInfix(stream));
    }
}

ProofSystem::~ProofSystem()
{
    for (Formula* axiom: axioms)
    {
        delete axiom;
    }
}

int ProofSystem::isAxiom(Formula* formula) const
{
    map<char, Formula*> substitutions;
    int type = 1;

    for (Formula* axiom: axioms)
    {
        if (axiom->matches(formula, substitutions))
        {
            return type;
        }
        substitutions.clear();
        type++;
    }
    return 0;
}

HilbertSystem::HilbertSystem()
: ProofSystem({"(A>(B>A))", "((A>(B>C))>((A>B)>(A>C)))", "((-A>-B)>(B>A))"})
{
    stringstream stream;

    stream << "(A>B)" << endl;
    modusPonens = parseInfix(stream);
}

HilbertSystem::~HilbertSystem()
{
    delete modusPonens;
}

list<int> HilbertSystem::isDeducible(Formula* formula,
                                     vector<ProofElement>& proof) const
{
    map<char, Formula*> substitutions;
    int premiseIndex = 1;
    int implicationIndex = 1;

    for (ProofElement implies: proof)
    {
        for (ProofElement implication: proof)
        {
            if (premiseIndex == implicationIndex)
            {
                continue;
            }
            substitutions.emplace('A', implies.getFormula());
            substitutions.emplace('B', formula);
            if (modusPonens->matches(implication.getFormula(), substitutions))
            {
                return {premiseIndex, implicationIndex};
            }
            substitutions.clear();
            implicationIndex++;
        }
        premiseIndex++;
        implicationIndex = 0;
    }
    return list<int>();
}
