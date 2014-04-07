#ifndef PROPOSITIONAL_FORMULA_HPP
#define	PROPOSITIONAL_FORMULA_HPP

#include <map>

using namespace std;

//! Language of connectives.

/**
 * Language to output connectives in.
 */
enum Language
{
    ASCII, ///< ASCII characters.
    WORDS, ///< English words.
    TEX ///< LaTeX language.
};

// Forward declaration for type definition purposes.
class PropositionalFormula;

// Type definitions for simplification purposes.
typedef map<Language, string> Dictionary; ///< Output language dictionary.
typedef map<char, PropositionalFormula *> Substitutions; ///< Axiom formulas substitutions.

//! Propositional formula.

/**
 * Formulas can be trivial (e.g. 'A') or composite (e.g. '-(A+B)').
 */
class PropositionalFormula
{
protected:
    static map<char, Dictionary> dictionary; ///< Output language dictionary.
    char character; ///< Characteristic character.
public:
    PropositionalFormula(char);
    virtual ~PropositionalFormula();
    /**
     * Characteristic character getter.
     * @return Characteristic character.
     */
    char getCharacter() const;
    /**
     * Returns a textual representation of this formula in prefix.
     * @param language Language of connectives.
     * @return Textual representation of this formula.
     */
    virtual string printPrefix(Language language) const = 0;
    /**
     * Returns a textual representation of this formula in infix.
     * @param language Language of connectives.
     * @return Textual representation of this formula.
     */
    virtual string printInfix(Language language) const = 0;
    /**
     * Returns a textual representation of this formula in postfix.
     * @param language Language of connectives.
     * @return Textual representation of this formula.
     */
    virtual string printPostfix(Language language) const = 0;
    /**
     * Checks whether given formula matches this one.
     * @param formula Formula to be matched.
     * @return Whether the given formula matches this one.
     */
    virtual bool matchesFormula(PropositionalFormula * formula) const = 0;
    /**
     * Checks whether given formula matches this axiom.
     * @param formula Formula to be matched.
     * @return Whether the given formula matches this axiom.
     */
    virtual bool matchesAxiom(PropositionalFormula * formula, Substitutions & substitutions)
    const = 0;
};

//! Proposition.

/**
 * Trivial formula consisting of one proposition.
 */
class Proposition : public PropositionalFormula
{
public:
    Proposition(char);
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool matchesFormula(PropositionalFormula * formula) const;
    virtual bool matchesAxiom(PropositionalFormula *, Substitutions & substitutions) const;
};

//! Operator.

/**
 * Formula consisting of one connective and several formulas.
 */
class Operator : public PropositionalFormula
{
public:
    Operator(char);
    /**
     * Assigns given formula as a first unset operand from the beginning.
     * @param formula Formula to be set as an operand.
     * @return Unset operands count after this operation.
     */
    virtual int append(PropositionalFormula * formula) = 0;
    /**
     * Assigns given formula as a first unset operand from the end.
     * @param formula Formula to be set as an operand.
     * @return Unset operands count after this operation.
     */
    virtual int insert(PropositionalFormula * formula) = 0;
};

//! Unary operator.

/**
 * Operator taking one operand.
 */
class UnaryOperator : public Operator
{
private:
    PropositionalFormula * operand = NULL; ///< Operand
public:
    UnaryOperator(char);
    virtual ~UnaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool matchesFormula(PropositionalFormula *) const;
    virtual bool matchesAxiom(PropositionalFormula *, Substitutions & substitutions) const;
    virtual int append(PropositionalFormula *);
    virtual int insert(PropositionalFormula *);
};

//! Binary operator.

/**
 * Operator taking two operands.
 */
class BinaryOperator : public Operator
{
private:
    PropositionalFormula * left = NULL; ///< Left operand
    PropositionalFormula * right = NULL; ///< Right operand
public:
    BinaryOperator(char);
    virtual ~BinaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool matchesFormula(PropositionalFormula *) const;
    virtual bool matchesAxiom(PropositionalFormula *, Substitutions & substitutions) const;
    virtual int append(PropositionalFormula *);
    virtual int insert(PropositionalFormula *);
};

#endif	/* PROPOSITIONAL_FORMULA_HPP */
