#ifndef TARGET_HPP
#define	TARGET_HPP

#include "configuration.hpp"

using namespace std;

//! Default execution target.

/**
 * Parse formulas only.
 * @param configuration Program configuration structure.
 * @return Program exit status.
 */
int executeDefault(Configuration * configuration);

//! Axiom instance checker.

/**
 * Check whether a formula is an axiom instance.
 * @param configuration Program configuration structure.
 * @return Program exit status.
 */
int executeAxiomCheck(Configuration * configuration);

//! Valid proof checker.

/**
 * Check whether a sequence of formulas is a valid proof.
 * @param configuration Program configuration structure.
 * @return Program exit status.
 */
int executeProofCheck(Configuration * configuration);

#endif
