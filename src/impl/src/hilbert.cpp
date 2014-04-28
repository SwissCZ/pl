#include "hilbert.hpp"
#include "parse.hpp"

#include <sstream>

using namespace std;

Hilbert::Hilbert()
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

Hilbert::~Hilbert()
{
    for (Formula * formula : axioms)
    {
        delete formula;
    }
    delete modusPonens;
}

int Hilbert::validateAxiom(Formula * formula) const
{
    int type = 1;
    Substitutions substitutions;

    for (Formula * axiom : axioms)
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

string * Hilbert::proveFormula(Formula * formula,
                               vector<Formula *> & proof) const
{
    int premiseOrder = 0;
    int implicationOrder = 0;
    Substitutions substitutions;
    stringstream stream;

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
            substitutions.emplace('A', premise);
            substitutions.emplace('B', formula);
            if (modusPonens->matches(implication, substitutions))
            {
                stream << "Provable via modus ponens using formulas " <<
                        premiseOrder << " and " << implicationOrder << ".";
                return new string(stream.str());
            }
            substitutions.clear();
        }
        implicationOrder = 0;
    }
    return NULL;
}
