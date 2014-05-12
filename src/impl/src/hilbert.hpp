#ifndef HILBERT_HPP
#define	HILBERT_HPP

#include <list>

#include "formula.hpp"
#include "proof.hpp"

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
    int isAxiom(Formula * formula) const;
    /**
     * Checks whether given formula is deducible using the modus ponens rule.
     * @param formula Formula to be deduced via modus ponens.
     * @param proof Proof within which given formula has to be deduced.
     * @return Premise and implication index or null if it is not deducible.
     */
    int * isDeducible(Formula * formula, Proof & proof) const;
};

const Hilbert hilbert;

#endif
