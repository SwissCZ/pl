#ifndef OPERATION_HPP
#define	OPERATION_HPP

/**
 * Logical operations. Supported logical operators.
 */
enum Operation
{
    NEGATION, ///< not A
    CONJUNCTION, ///< A and B
    DISJUNCTION, ///< A or B
    IMPLICATION, ///< if A then B
    EQUIVALENCE ///< A if and only if B
};

#endif	/* OPERATION_HPP */
