#include <sstream>

#include "hilbert.hpp"
#include "parse.hpp"

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

int Hilbert::isAxiom(Formula * formula) const
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

int * Hilbert::isDeducible(Formula * formula, Proof & proof) const
{
    int premiseOrder = 0;
    int implicationOrder = 0;
    Substitutions substitutions;
    stringstream stream;
    int * indexes = new int[2];

    for (Formula * premise : proof.getFormulas())
    {
        premiseOrder++;
        for (Formula * implied : proof.getFormulas())
        {
            implicationOrder++;
            if (premise == implied)
            {
                continue;
            }
            substitutions.emplace('A', premise);
            substitutions.emplace('B', formula);
            if (modusPonens->matches(implied, substitutions))
            {
                indexes[0] = premiseOrder;
                indexes[1] = implicationOrder;
                return indexes;
            }
            substitutions.clear();
        }
        implicationOrder = 0;
    }
    return NULL;
}
