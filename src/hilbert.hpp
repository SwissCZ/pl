#ifndef HILBERT_HPP
#define	HILBERT_HPP

#include "formula.hpp"
#include "provability.hpp"

#include <list>

using namespace std;

/**
 * Hilbert's axiom system
 */
class HilbertSystem
{
private:
    list<Formula *> axioms; ///< Hilbert axioms
    Formula * modusPonens; ///< Modus ponens implication formula
public:
    HilbertSystem();
    /**
     * Checks whether given formula is an axiom.
     * @param formula Formula to be validated as an axiom
     * @return Axiom type given formula is of or 0 if it is not an axiom
     */
    int validateAxiom(Formula * formula) const;
    /**
     * Checks whether given formula is provable using the modus ponens rule.
     * @param formula Formula to be validated within the proof
     * @param proof Proof within which the given formula is to be validated
     * @return Formula modus ponens provability validation result
     */
    Provability * validateModusPonens(Formula * formula, list<Formula *> proof)
    const;
};

#endif	/* HILBERT_HPP */
