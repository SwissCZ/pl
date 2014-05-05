#ifndef HILBERT_HPP
#define	HILBERT_HPP

#include "formula.hpp"
#include "proof.hpp"

#include <list>

using namespace std;

//! Hilbert system.

/**
 * Functionality of Hilbert system.
 */
class HilbertSystem
{
private:
    list<Formula *> axioms; ///< Hilbert axioms.
    Formula * modusPonens; ///< Modus ponens implication formula.
public:
    HilbertSystem();
    ~HilbertSystem();
    /**
     * Checks whether given formula is an axiom.
     * @param formula Formula to be validated as an axiom.
     * @return Axiom type given formula is of or 0 if it is not an axiom.
     */
    int isAxiom(Formula * formula) const;
    /**
     * Checks whether given formula is provable using the modus ponens rule.
     * @param formula Formula to be proved via modus ponens.
     * @param proof Proof within which given formula has to be proved.
     * @return Premise and implication index or null if it is not provable.
     */
    int * isProvable(Formula * formula, Proof & proof) const;
};

const HilbertSystem hilbertSystem;

#endif
