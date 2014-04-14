#ifndef HILBERT_HPP
#define	HILBERT_HPP

#include "formula.hpp"

#include <list>
#include <string>
#include <vector>

using namespace std;

//! Hilbert system.

/**
 * Functionality of Hilbert system.
 */
class Hilbert
{
private:
    list<Formula *> axioms; ///< Hilbert axioms.
    Formula * modusPonens; ///< Modus ponens implication formula.
public:
    Hilbert();
    ~Hilbert();
    /**
     * Checks whether given formula is an axiom.
     * @param formula Formula to be validated as an axiom.
     * @return Axiom type given formula is of or 0 if it is not an axiom.
     */
    int validateAxiom(Formula * formula) const;
    /**
     * Checks whether given formula is provable using the modus ponens rule.
     * @param formula Formula to be proved via modus ponens.
     * @param proof Proof within which given formula has to be proved.
     * @return Formula provability description or null if it is not provable.
     */
    string * proveFormula(Formula * formula, vector<Formula *> & proof) const;
};

#endif
