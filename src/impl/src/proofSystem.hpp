#ifndef PROOF_SYSTEM_HPP
#define	PROOF_SYSTEM_HPP

#include <list>
#include <string>
#include <vector>

#include "formula.hpp"
#include "proofElement.hpp"

using namespace std;

//! Proof system

/**
 * Propositional calculus proof system.
 */
class ProofSystem
{
private:
    list<Formula*> axioms;
    ///< Proof system axioms
public:
    ProofSystem(list<string>);
    virtual ~ProofSystem();

    /**
     * Verifies whether given formula is an axiom.
     * @param formula Formula to be verified as an axiom
     * @return Axiom type given formula is or 0 when formula is not an axiom
     */
    int isAxiom(Formula* formula) const;

    /**
     * Verifies whether given formula is deducible using the deduction rules.
     * @param formula Formula to be deduced within given proof
     * @param proof Proof within which given formula is to be deduced
     * @return Deducing formulas indexes, empty when formula is not deducible
     */
    virtual list<int> isDeducible(Formula* formula,
                                  vector<ProofElement>& proof) const = 0;
};

//! Hilbert's proof system

/**
 * Proof system deducing formulas via the modus ponens rule.
 */
class HilbertSystem: public ProofSystem
{
private:
    Formula* modusPonens;
    ///< Modus ponens implication formula
public:
    HilbertSystem();
    virtual ~HilbertSystem();
    virtual list<int> isDeducible(Formula*,
                                  vector<ProofElement>&) const;
};

#endif
