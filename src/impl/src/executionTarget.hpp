#ifndef EXECUTION_TARGET_HPP
#define	EXECUTION_TARGET_HPP

#include "configuration.hpp"

using namespace std;

//! Proof handler target

/**
 * Targets of the proof handler target.
 */
enum ProofTarget
{
    VERIFY, ///< Verify the proof only
    MINIMIZE ///< Minimize the verified proof
};

//! Program execution target

/**
 * Program can peform one target per execution.
 */
class ExecutionTarget
{
public:
    virtual ~ExecutionTarget();

    /**
     * Executes the target.
     * @param config Program configuration
     * @return Program exit status
     */
    virtual int execute(Configuration& config) const = 0;
};

//! Axiom verification

/**
 * Verify each formula as an axiom.
 */
class AxiomChecker: public ExecutionTarget
{
public:
    virtual int execute(Configuration&) const;
};

//! Default execution target

/**
 * Parse formulas only.
 */
class DefaultTarget: public ExecutionTarget
{
public:
    virtual int execute(Configuration&) const;
};

//! Proof handling

/**
 * Verify or minimize a proof given as a sequence of formulas.
 */
class ProofHandler: public ExecutionTarget
{
private:
    unsigned premises;
    ///< Input premises count

    ProofTarget target;
    ///< Proof handler target
public:
    ProofHandler(unsigned,
                 ProofTarget);

    virtual int execute(Configuration&) const;
};

#endif
