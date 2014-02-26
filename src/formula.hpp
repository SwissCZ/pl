#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <map>
#include <string>

#include "operation.hpp"
#include "language.hpp"

using namespace std;

const map<Operation, std::map<Language, const char * >> languageMap = {
    {NEGATION,
        {
            {ASCII, "-"},
            {COMMON, " not "},
            {TEX, "\\neg"}
        }},
    {CONJUNCTION,
        {
            {ASCII, "."},
            {COMMON, " and "},
            {TEX, "\\wedge"}
        }},
    {DISJUNCTION,
        {
            {ASCII, "+"},
            {COMMON, " or "},
            {TEX, "\\vee"}
        }},
    {IMPLICATION,
        {
            {ASCII, ">"},
            {COMMON, " implies "},
            {TEX, "\\rightarrow"}
        }},
    {EQUIVALENCE,
        {
            {ASCII, "="},
            {COMMON, " is "},
            {TEX, "\\leftrightarrow"}
        }}
}; ///< Output language definition

/**
 * Propositional formula. Formulas could be trivial (A) or more sophisticated -(A+B).
 */
class Formula
{
public:
    /**
     * Destructor causes chained destruction of the whole expression tree.
     */
    virtual ~Formula();
    /**
     * Creates a textual representation of this formula in the prefix notation and the specified language.
     * @param Output language
     * @return String representation of this formula
     */
    virtual string printPrefix(Language) const = 0;
    /**
     * The same as printPrefix but infix notation is used.
     * @param Language of connectives
     * @return String representation of this formula
     */
    virtual string printInfix(Language) const = 0;
    /**
     * The same as printPrefix but postfix notation is used.
     * @param Language of connectives
     * @return String representation of this formula
     */
    virtual string printPostfix(Language) const = 0;
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
    Operation operation; ///< Operation representing this operator
public:
    Operator(Operation);
    /**
     * Appends a formula as an operand to the first available position.
     * @param Formula to be set as an operand
     * @return Unset operands count
     */
    virtual int appendFirst(Formula *) = 0;
    /**
     * Appends a formula as an operand to the last available position.
     * @param Formula to be set as an operand
     * @return Unset operands count
     */
    virtual int appendLast(Formula *) = 0;
};

/**
 * Unary operator. Operator with arity of 1.
 */
class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL; ///< Operand
public:
    UnaryOperator(Operation);
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
    BinaryOperator(Operation);
    virtual ~BinaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual int appendFirst(Formula *);
    virtual int appendLast(Formula *);
};

#endif	/* FORMULA_HPP */
