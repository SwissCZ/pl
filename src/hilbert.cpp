#include "hilbert.hpp"
#include "parse.hpp"

#include <sstream>

using namespace std;

HilbertSystem::HilbertSystem()
{
    stringstream stream;
    list<string> strings = {"(A>(B>A))",
                            "((A>(B>C))>((A>B)>(A>C)))",
                            "((-A>-B)>(B>A))"};

    for (string string : strings)
    {
        stream << string << endl;
        axioms.push_back(parseInfix(stream));
    }
    stream << "(A>B)" << endl;
    modusPonens = parseInfix(stream);
}

int HilbertSystem::validateAxiom(Formula * formula) const
{
    int type = 1;
    for (Formula * axiom : axioms)
    {
        if (axiom->matchesSubstitutions(formula))
        {
            return type;
        }
        type++;
    }
    return 0;
}

Provability * HilbertSystem::validateModusPonens(Formula * formula,
                                                 list<Formula *> proof) const
{
    int premiseOrder = 0;
    int implicationOrder = 0;
    SubstituteMap * substitutions = NULL;

    for (Formula * premise : proof)
    {
        premiseOrder++;
        for (Formula * implication : proof)
        {
            implicationOrder++;
            if (premise == implication)
            {
                continue;
            }
            substitutions = new SubstituteMap{
                {'A', premise},
                {'B', formula}
            };
            if (modusPonens->matchesSubstitutions(implication, substitutions))
            {
                delete substitutions;
                return new ProvableResult(premiseOrder, implicationOrder);
            }
            delete substitutions;
        }
        implicationOrder = 0;
    }
    return new InprovableResult();
}
