#ifndef EXECUTION_TARGET_HPP
#define	EXECUTION_TARGET_HPP

#include "configuration.hpp"

using namespace std;

//! Program execution target.

/**
 * Program can peform one target per execution.
 */
class ExecutionTarget
{
public:
    virtual ~ExecutionTarget();

    /**
     * Executes the target.
     * @param config Program configuration.
     * @return Program exit status.
     */
    virtual int execute(Configuration& config) const = 0;
};

//! Default execution target.

/**
 * Parse formulas only.
 */
class DefaultTarget: public ExecutionTarget
{
public:
    virtual int execute(Configuration&) const;
};

//! Axiom verification.

/**
 * Verify each formula as an axiom.
 */
class AxiomChecker: public ExecutionTarget
{
public:
    virtual int execute(Configuration&) const;
};

//! Proof handling.

/**
 * Verify or optimize a proof given as a sequence of formulas.
 */
class ProofHandler: public ExecutionTarget
{
private:
    unsigned premises;
    ///< Input premises count.

    bool optimize;
    ///< Proof optimization flag.
public:
    ProofHandler(unsigned,
                 bool);

    virtual int execute(Configuration&) const;
};

#endif
