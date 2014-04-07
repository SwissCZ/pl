#ifndef EXECUTION_TARGET_HPP
#define	EXECUTION_TARGET_HPP

#include "hilbertSystem.hpp"
#include "programConfiguration.hpp"
#include "propositionalFormula.hpp"

#include <list>

using namespace std;

//! Program execution target.

/**
 * Execution target the program can execute.
 */
class ExecutionTarget
{
public:
    virtual ~ExecutionTarget();
    /**
     * Execute the program target.
     * @param configuration Program configuration.
     * @return Program exit status.
     */
    virtual int execute(ProgramConfiguration * configuration) = 0;
};

//! Default execution target.

/**
 * Parse formulas, report errors and exit.
 */
class DefaultTarget : public ExecutionTarget
{
public:
    virtual int execute(ProgramConfiguration *);
};

//! Hilbert's axiom system dependent target.

/**
 * Target depending on the Hilbert's axiom system.
 */
class HilbertTarget : public ExecutionTarget
{
protected:
    HilbertSystem system; ///< Axiomatic system to work with.
};

//! Valid axiom checker.

/**
 * Check whether a formula is a valid axiom.
 */
class AxiomCheck : public HilbertTarget
{
public:
    virtual int execute(ProgramConfiguration *);
};

//! Valid proof checker.

/**
 * Check whether a sequence of formulas is a valid proof.
 */
class ProofCheck : public HilbertTarget
{
private:
    list<PropositionalFormula *> validProof; ///< So far valid proof.
public:
    virtual ~ProofCheck();
    virtual int execute(ProgramConfiguration *);
};

#endif	/* EXECUTION_TARGET_HPP */
