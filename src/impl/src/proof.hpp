#ifndef PROOF_HPP
#define	PROOF_HPP

#include "formula.hpp"

#include <list>

using namespace std;

//! Propositional proof

/**
 * Proof of the propositional calculus.
 */
class Proof
{
private:
    list<Formula *> formulas; ///< Formulas this proof consists of.
public:
    ~Proof();
    /**
     * Returns a list of formulas this proof consists of.
     * @return List of formulas this proof consists of.
     */
    const list<Formula *> & getFormulas() const;
    /**
     * Checks whether this proof already contains given formula.
     * @param formula Formula to be checked.
     * @return True if this proof already contains given formula.
     */
    bool contains(Formula * formula) const;
    /**
     * Appends given formula to this proof.
     * @param formula Formula to be appended.
     */
    void add(Formula * formula);
};

#endif
