#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include "language.hpp"

#include <cstddef>
#include <map>

using namespace std;

class Formula;

typedef map<Language, string> LanguageMap;
typedef map<char, Formula *> SubstituteMap;

//! Propositional formula

/**
 * Formulas can be trivial (e.g. 'A') or composite (e.g. '-(A+B)').
 */
class Formula
{
protected:
    static map<char, LanguageMap> INPUT_LANGUAGE;

    char character; ///< Identifying character
public:
    Formula(char);
    /**
     * Causes chained destruction of the expression tree.
     */
    virtual ~Formula();
    /**
     * Identifying character getter.
     * @return Identifying character
     */
    char getCharacter() const;
    /**
     * Returns a textual representation of this formula in the prefix notation.
     * @param language Language of connectives
     * @return Textual representation of this formula
     */
    virtual string printPrefix(Language language) const = 0;
    /**
     * Returns a textual representation of this formula in the infix notation.
     * @param language Language of connectives
     * @return Textual representation of this formula
     */
    virtual string printInfix(Language language) const = 0;
    /**
     * Returns a textual representation of this formula in the postfix notation.
     * @param language Language of connectives
     * @return Textual representation of this formula
     */
    virtual string printPostfix(Language language) const = 0;
    /**
     * Checks whether given formula matches this one.
     * @param formula Formula to be matched
     * @return Whether the given formula matches this one
     */
    virtual bool matchesFormula(Formula * formula) const = 0;
    /**
     * Checks whether given formula matches this one.
     * @param formula Formula to be matched
     * @return Whether the given formula matches this one
     */
    virtual bool matchesSubstitutions(Formula * formula, SubstituteMap *
                                   substitutions = new SubstituteMap())
    const = 0;
};

//! Proposition

/**
 * Trivial formula consisting of one proposition.
 */
class Proposition : public Formula
{
public:
    Proposition(char);
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool matchesFormula(Formula * formula) const;
    virtual bool matchesSubstitutions(Formula *, SubstituteMap * substitutions
                                   = new SubstituteMap()) const;
};

//! Operator

/**
 * Formula consisting of one connective and several formulas.
 */
class Operator : public Formula
{
public:
    Operator(char);
    /**
     * Assigns given formula to the first unset position from the beginning.
     * @param formula Formula to be set as an operand
     * @return Unset operands count after this operation
     */
    virtual int append(Formula * formula) = 0;
    /**
     * Assigns given formula to the first unset position from the end.
     * @param formula Formula to be set as an operand
     * @return Unset operands count after this operation
     */
    virtual int insert(Formula * formula) = 0;
};

//! Unary operator

/**
 * Operator taking one operand.
 */
class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL; ///< The operand
public:
    UnaryOperator(char);
    virtual ~UnaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool matchesFormula(Formula *) const;
    virtual bool matchesSubstitutions(Formula *, SubstituteMap * substitutions
                                   = new SubstituteMap()) const;
    virtual int append(Formula *);
    virtual int insert(Formula *);
};

//! Binary operator

/**
 * Operator taking two operands.
 */
class BinaryOperator : public Operator
{
private:
    Formula * leftOperand = NULL; ///< The left operand
    Formula * rightOperand = NULL; ///< The right operand
public:
    BinaryOperator(char);
    virtual ~BinaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool matchesFormula(Formula *) const;
    virtual bool matchesSubstitutions(Formula *, SubstituteMap * substitutions
                                   = new SubstituteMap()) const;
    virtual int append(Formula *);
    virtual int insert(Formula *);
};

#endif	/* FORMULA_HPP */
