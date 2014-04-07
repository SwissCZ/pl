#include "hilbertSystem.hpp"
#include "parseFunctions.hpp"

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
    implication = parseInfix(stream);
}

HilbertSystem::~HilbertSystem()
{
    for (PropositionalFormula * formula : axioms)
    {
        delete formula;
    }
    delete implication;
}

int HilbertSystem::validateAxiom(PropositionalFormula * formula) const
{
    int type = 1;
    Substitutions substitutions;
    for (PropositionalFormula * axiom : axioms)
    {
        if (axiom->matchesAxiom(formula, substitutions))
        {
            return type;
        }
        substitutions.clear();
        type++;
    }
    return 0;
}

string * HilbertSystem::proveFormula(PropositionalFormula * formula,
                                     list<PropositionalFormula *> proof) const
{
    int premiseOrder = 0;
    int implicationOrder = 0;
    Substitutions substitutions;
    stringstream stream;

    for (PropositionalFormula * premise : proof)
    {
        premiseOrder++;
        for (PropositionalFormula * implication : proof)
        {
            implicationOrder++;
            if (premise == implication)
            {
                continue;
            }
            substitutions.emplace('A', premise);
            substitutions.emplace('B', formula);
            if (implication->matchesAxiom(implication, substitutions))
            {
                stream << "Provable via modus ponens using formulas " <<
                        premiseOrder << " and " << implicationOrder << ".";
                return new string(stream.str());
            }
            substitutions.clear();
        }
        implicationOrder = 0;
    }
    stream << "Inprovable within this proof.";
    return new string(stream.str());
}
