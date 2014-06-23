#include <sstream>

#include "parseFormula.hpp"
#include "proofSystem.hpp"

ProofSystem::ProofSystem(list<string> axiomStrings)
{
    stringstream stream;

    for (string axiomString : axiomStrings)
    {
        stream << axiomString << endl;
        axioms.push_back(parseInfix(stream));
    }
}

ProofSystem::~ProofSystem()
{
    for (Formula* axiom : axioms)
    {
        delete axiom;
    }
}

unsigned ProofSystem::isAxiom(Formula* formula) const
{
    map<char, Formula*> substitutions;
    unsigned type = 1;

    for (Formula* axiom : axioms)
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

list<unsigned> HilbertSystem::isDeducible(Formula* formula,
                                          vector<ProofMember*>& proof) const
{
    map<char, Formula*> substitutions;
    unsigned impliesIndex = 1;
    unsigned implicationIndex = 1;

    for (ProofMember* implies : proof)
    {
        for (ProofMember* implication : proof)
        {
            if (impliesIndex == implicationIndex)
            {
                implicationIndex++;
                continue;
            }
            substitutions.emplace('A', implies->getFormula());
            substitutions.emplace('B', formula);
            if (modusPonens->matches(implication->getFormula(), substitutions))
            {
                return
                {
                    impliesIndex, implicationIndex
                };
            }
            substitutions.clear();
            implicationIndex++;
        }
        impliesIndex++;
        implicationIndex = 1;
    }
    return list<unsigned>();
}
