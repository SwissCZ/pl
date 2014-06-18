#ifndef PROOF_ELEMENT_HPP
#define	PROOF_ELEMENT_HPP

#include <list>

#include "formula.hpp"

using namespace std;

//! Proof element

/**
 * Proof element as a complex structure.
 */
class ProofElement
{
private:
    Formula* formula;
    ///< Formula representing this proof element

    list<ProofElement*> witnesses;
    ///< Formulas deducing this one

    bool preserve = false;
    ///< Optimal proof component flag
public:
    ProofElement(Formula*,
                 list<ProofElement*> = list<ProofElement*>());
    ~ProofElement();

    /**
     * Formula getter.
     * @return Formula representing this proof element
     */
    Formula* getFormula() const;

    /**
     * Witnesses getter.
     * @return Formulas deducing this one
     */
    list<ProofElement*> getWitnesses() const;

    /**
     * Optimal proof component flag getter.
     * @return Optimal proof component flag
     */
    bool getPreserve() const;

    /**
     * Optimal proof component flag setter.
     * @param preserve Optimal proof component flag flag to be set
     */
    void setPreserve(bool preserve);
};

#endif
