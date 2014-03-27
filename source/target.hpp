#ifndef TARGET_HPP
#define	TARGET_HPP

#include "formula.hpp"
#include "hilbert.hpp"

#include <list>

using namespace std;

//! Program execution target

/**
 * The target the program can be set to execute.
 */
class Target
{
protected:
    static HilbertSystem system; ///< The axiomatic system
public:
    virtual ~Target();
    /**
     * Perform next step of the program execution.
     * @param formula Formula to be processed
     * @return Whether to continue the program execution
     */
    virtual bool next(Formula * formula);
};

//! Axiom checker

/**
 * Check whether each formula is an axiom.
 */
class AxiomChecker : public Target
{
public:
    virtual bool next(Formula *);
};


//! Proof checker

/**
 * Check whether the sequence of formulas is a valid proof.
 */
class ProofChecker : public Target
{
private:
    list<Formula *> proof; ///< The valid proof so far
public:
    virtual bool next(Formula *);
};

#endif	/* TARGET_HPP */
