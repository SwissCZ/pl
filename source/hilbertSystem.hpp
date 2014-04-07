#ifndef HILBERT_SYSTEM_HPP
#define	HILBERT_SYSTEM_HPP

#include "propositionalFormula.hpp"

#include <list>
#include <string>

using namespace std;

//! Hilbert's axiom system.

/**
 * Axioms and rules of Hilbert's axiom system.
 */
class HilbertSystem
{
private:
    list<PropositionalFormula *> axioms; ///< Hilbert axioms
    PropositionalFormula * implication; ///< Modus ponens implication formula
public:
    HilbertSystem();
    ~HilbertSystem();
    /**
     * Checks whether given formula is an axiom.
     * @param formula Formula to be validated as an axiom.
     * @return Axiom type given formula is of or 0 if it is not an axiom.
     */
    int validateAxiom(PropositionalFormula * formula) const;
    /**
     * Checks whether given formula is provable using the modus ponens rule.
     * @param formula Formula to be proved.
     * @param proof Proof within which given formula has to be proved.
     * @return Formula provability message or null if it is not provable.
     */
    string * proveFormula(PropositionalFormula * formula, list<PropositionalFormula *> proof) const;
};

#endif	/* HILBERT_SYSTEM_HPP */
