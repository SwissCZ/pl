#ifndef TARGET_HPP
#define	TARGET_HPP

#include "configuration.hpp"
#include "formula.hpp"
#include "hilbert.hpp"

#include <vector>

using namespace std;

//! Program execution target.

/**
 * Execution target the program can perform.
 */
class Target
{
public:
    virtual ~Target();
    /**
     * Performs the execution target.
     * @param configuration Program configuration structure.
     * @return Program exit status.
     */
    virtual int execute(Configuration * configuration) = 0;
};

//! Default execution target.

/**
 * Parse formulas only.
 */
class DefaultTarget : public Target
{
public:
    virtual int execute(Configuration *);
};

//! Hilbert system dependent target.

/**
 * Target performed within the Hilbert axiom system.
 */
class HilbertTarget : public Target
{
protected:
    Hilbert system; ///< Axiomatic system to work with.
};

//! Valid axiom checker.

/**
 * Check whether a formula is a valid axiom.
 */
class AxiomCheck : public HilbertTarget
{
public:
    virtual int execute(Configuration *);
};

//! Valid proof checker.

/**
 * Check whether a sequence of formulas is a valid proof.
 */
class ProofCheck : public HilbertTarget
{
private:
    vector<Formula *> validProof; ///< So far valid proof.

    /**
     * Checks whether the proof already contains given formula.
     * @param formula Formula to be searched for.
     * @return Whether the proof already contains given formula.
     */
    bool contains(Formula * formula) const;
public:
    virtual ~ProofCheck();
    virtual int execute(Configuration *);
};

#endif
