#ifndef PROOF_MEMBER_HPP
#define	PROOF_MEMBER_HPP

#include <list>

#include "formula.hpp"

using namespace std;

//! Proof member

/**
 * Proof member as a complex structure.
 */
class ProofMember
{
private:
    Formula* formula;
    ///< Formula representing this proof member

    list<ProofMember*> witnesses;
    ///< Formulas deducing this one

    bool preserve = false;
    ///< Minimal proof component flag
public:
    ProofMember(Formula*,
                list<ProofMember*> = list<ProofMember*>());
    ~ProofMember();

    /**
     * Formula getter.
     * @return Formula representing this proof member
     */
    Formula* getFormula() const;

    /**
     * Witnesses getter.
     * @return Witnesses of this formula
     */
    const list<ProofMember*>& getWitnesses() const;

    /**
     * Minimal proof component flag getter.
     * @return Minimal proof component flag
     */
    bool getPreserve() const;

    /**
     * Minimal proof component flag setter.
     * @param preserve Minimal proof component flag flag to be set
     */
    void setPreserve(bool preserve);
};

#endif
