#ifndef HILBERT_HPP
#define	HILBERT_HPP

#include "formula.hpp"
#include "provability.hpp"

#include <list>

using namespace std;

//! Hilbert system

/**
 * Axioms and rules of Hilbert system.
 */
class HilbertSystem
{
private:
    list<Formula *> axioms; ///< Hilbert axioms
    Formula * implication; ///< Modus ponens implication formula
public:
    HilbertSystem();
    ~HilbertSystem();
    /**
     * Checks whether given formula is an axiom.
     * @param formula Formula to be validated as an axiom.
     * @return Axiom type given formula is of or 0 if it is not an axiom.
     */
    int validateAxiom(Formula * formula) const;
    /**
     * Checks whether given formula is provable using the modus ponens rule.
     * @param formula Formula to be proved.
     * @param proof Proof within which given formula is to be proved.
     * @return Formula modus ponens provability validation result.
     */
    Provability * validateModusPonens(Formula * formula, list<Formula *> proof)
    const;
};

#endif	/* HILBERT_HPP */
