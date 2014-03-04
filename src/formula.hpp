#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <map>
#include <string>

#include "language.hpp"
#include "connective.hpp"

using namespace std;

const map<Connective, std::map<Language, const char * >> languageMap = {
    {NEGATION,
        {
            {ASCII, "-"},
            {WORDS, " not "},
            {TEX, "\\neg"}
        }},
    {CONJUNCTION,
        {
            {ASCII, "."},
            {WORDS, " and "},
            {TEX, "\\wedge"}
        }},
    {DISJUNCTION,
        {
            {ASCII, "+"},
            {WORDS, " or "},
            {TEX, "\\vee"}
        }},
    {IMPLICATION,
        {
            {ASCII, ">"},
            {WORDS, " implies "},
            {TEX, "\\rightarrow"}
        }},
    {EQUIVALENCE,
        {
            {ASCII, "="},
            {WORDS, " iff "},
            {TEX, "\\leftrightarrow"}
        }}
}; ///< Output language definition

/**
 * Propositional formula. Formulas could be trivial (A) or more sophisticated
 * -(A+B).
 */
class Formula
{
public:
    /**
     * Causes chained destruction of the whole expression tree.
     */
    virtual ~Formula();
    /**
     * Creates a textual representation of this formula in the prefix notation
     * and the specified language.
     * @param language Output language
     * @return String representation of this formula
     */
    virtual string printPrefix(Language language) const = 0;
    /**
     * Creates a textual representation of this formula in the infix notation
     * and the specified language.
     * @param language Language of connectives
     * @return String representation of this formula
     */
    virtual string printInfix(Language language) const = 0;
    /**
     * Creates a textual representation of this formula in the postfix notation
     * and the specified language.
     * @param language Language of connectives
     * @return String representation of this formula
     */
    virtual string printPostfix(Language language) const = 0;
};

/**
 * Proposition. Proposition is a trivial formula.
 */
class Proposition : public Formula
{
private:
    char character; ///< Proposition identifier
public:
    Proposition(char);
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
};

/**
 * Operator. Operator is a formula which consists of several formulas.
 */
class Operator : public Formula
{
protected:
    Connective operation; ///< Operation represented by this operator
public:
    Operator(Connective);
    /**
     * Appends a formula as an operand to the first available position.
     * @param formula Formula to be set as an operand
     * @return Unset operands count
     */
    virtual int appendFirst(Formula * formula) = 0;
    /**
     * Appends a formula as an operand to the last available position.
     * @param formula Formula to be set as an operand
     * @return Unset operands count
     */
    virtual int appendLast(Formula * formula) = 0;
};

/**
 * Unary operator. Operator with arity of 1.
 */
class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL; ///< Operand
public:
    UnaryOperator(Connective);
    virtual ~UnaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual int appendFirst(Formula *);
    virtual int appendLast(Formula *);
};

/**
 * Binary operator. Operator with arity of 2.
 */
class BinaryOperator : public Operator
{
private:
    Formula * leftOperand = NULL; ///< Left operand
    Formula * rightOperand = NULL; ///< Right operand
public:
    BinaryOperator(Connective);
    virtual ~BinaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual int appendFirst(Formula *);
    virtual int appendLast(Formula *);
};

#endif	/* FORMULA_HPP */
