#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <cstddef>
#include <map>

using namespace std;

//! Output language of connectives.

/**
 * Language to output connectives in when printing formulas.
 */
enum Language
{
    ASCII, ///< ASCII characters.
    WORDS, ///< English words.
    TEX ///< LaTeX language.
};

class Formula;

typedef map<Language, string> Dictionary; ///< Output language dictionary.
typedef map<char, Formula *> Substitutions; ///< Formula substitutions.

//! Propositional formula.

/**
 * Formula expression tree node.
 */
class Formula
{
protected:
    static const map<char, Dictionary> dictionary; ///< Output language dictionary.
    char character; ///< Character representation.
public:
    Formula(char);
    virtual ~Formula();
    /**
     * Character representation getter.
     * @return Character representation.
     */
    char getCharacter() const;
    /**
     * Returns a textual representation of this formula in prefix syntax.
     * @param language Language of connectives to use.
     * @return Textual representation of this formula in prefix syntax.
     */
    virtual string printPrefix(Language language) const = 0;
    /**
     * Returns a textual representation of this formula in infix syntax.
     * @param language Language of connectives to use.
     * @return Textual representation of this formula in infix syntax.
     */
    virtual string printInfix(Language language) const = 0;
    /**
     * Returns a textual representation of this formula in postfix syntax.
     * @param language Language of connectives to use.
     * @return Textual representation of this formula in postfix syntax.
     */
    virtual string printPostfix(Language language) const = 0;
    /**
     * Checks whether given formula equals to this one.
     * @param formula Formula to be compared with this one.
     * @return True if given formula equals to this one.
     */
    virtual bool equals(Formula * formula) const = 0;
    /**
     * Checks whether given formula matches this one.
     * @param formula Formula to be matched to this one.
     * @param substitutions Propositions substitutions of this formula.
     * @return True if given formula matches this one.
     */
    virtual bool matches(Formula * formula, Substitutions & substitutions) const = 0;
};

//! Proposition.

/**
 * Trivial formula consisting of a proposition.
 */
class Proposition : public Formula
{
public:
    Proposition(char);
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool equals(Formula *) const;
    virtual bool matches(Formula *, Substitutions &) const;
};

//! Operator.

/**
 * Formula consisting of a connective and several formulas.
 */
class Operator : public Formula
{
public:
    Operator(char);
    /**
     * Sets given formula as the first unset operand from the left.
     * @param formula Formula to be set as an operand.
     * @return True if all operands have been set.
     */
    virtual bool append(Formula * formula) = 0;
    /**
     * Set given formula as the last unset operand from the left.
     * @param formula Formula to be set as an operand.
     * @return True if all operands have been set.
     */
    virtual bool insert(Formula * formula) = 0;
};

//! Unary operator.

/**
 * Operator taking one operand.
 */
class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL; ///< Operand
public:
    UnaryOperator(char);
    virtual ~UnaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool equals(Formula *) const;
    virtual bool matches(Formula *, Substitutions &) const;
    virtual bool append(Formula *);
    virtual bool insert(Formula *);
};

//! Binary operator.

/**
 * Operator taking two operands.
 */
class BinaryOperator : public Operator
{
private:
    Formula * left = NULL; ///< Left operand
    Formula * right = NULL; ///< Right operand
public:
    BinaryOperator(char);
    virtual ~BinaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool equals(Formula *) const;
    virtual bool matches(Formula *, Substitutions &) const;
    virtual bool append(Formula *);
    virtual bool insert(Formula *);
};

#endif
