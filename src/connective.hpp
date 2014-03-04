#ifndef CONNECTIVE_HPP
#define	CONNECTIVE_HPP

/**
 * Logical operations. Supported logical operators.
 */
enum Connective
{
    NEGATION, ///< not A
    CONJUNCTION, ///< A and B
    DISJUNCTION, ///< A or B
    IMPLICATION, ///< A impliew B
    EQUIVALENCE ///< A iff B
};

#endif	/* CONNECTIVE_HPP */
