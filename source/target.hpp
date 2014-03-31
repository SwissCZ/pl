#ifndef TARGET_HPP
#define	TARGET_HPP

#include "configuration.hpp"
#include "formula.hpp"
#include "hilbert.hpp"

#include <list>

using namespace std;

//! Default target.

/**
 * Default program execution target the program execute.
 */
class Target
{
protected:
    static HilbertSystem system; ///< Axiomatic system to work within.
public:
    virtual ~Target();
    /**
     * Perform next step of the program execution.
     * @param configuration Program configuration.
     * @return Program exit code.
     */
    virtual int perform(Configuration * configuration);
};

//! Axiom checker.

/**
 * Check whether a formula is an axiom.
 */
class AxiomChecker : public Target
{
public:
    virtual int perform(Configuration *);
};


//! Proof checker.

/**
 * Check whether a sequence of formulas is a valid proof.
 */
class ProofChecker : public Target
{
private:
    list<Formula *> proof; ///< So-far-valid proof.
public:
    virtual ~ProofChecker();
    virtual int perform(Configuration *);
};

#endif	/* TARGET_HPP */
