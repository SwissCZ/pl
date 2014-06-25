#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <map>
#include <string>

using namespace std;

//! Output language of connectives

/**
 * Language to output connectives in when printing formulas.
 */
enum Language
{
    ASCII, ///< ASCII characters
    WORDS, ///< English words
    LATEX ///< LaTeX macros
};

//! Propositional formula

/**
 * Formula expression tree node.
 */
class Formula
{
protected:
    static map<char, map<Language, string>> dictionary;
    ///< Output connectives dictionary

    char character;
    ///< Representing character
public:
    Formula(char);
    virtual ~Formula();

    /**
     * Representing character getter.
     * @return Representing character
     */
    char getCharacter() const;

    /**
     * Returns a textual representation of this formula in prefix syntax.
     * @param language Language of connectives to use
     * @return Textual representation of this formula in prefix syntax
     */
    virtual string printPrefix(Language language) const = 0;

    /**
     * Returns a textual representation of this formula in infix syntax.
     * @param language Language of connectives to use
     * @return Textual representation of this formula in infix syntax
     */
    virtual string printInfix(Language language) const = 0;

    /**
     * Returns a textual representation of this formula in postfix syntax.
     * @param language Language of connectives to use
     * @return Textual representation of this formula in postfix syntax
     */
    virtual string printPostfix(Language language) const = 0;

    /**
     * Verifies whether given formula equals to this one.
     * @param formula Formula to be compared with this one
     * @return True if given formula equals to this one
     */
    virtual bool equals(Formula* formula) const = 0;

    /**
     * Verifies whether given formula matches this one.
     * @param formula Formula to be matched to this one
     * @param substitutions Propositions substitutions of this formula
     * @return True if given formula matches this one
     */
    virtual bool matches(Formula* formula,
                         map<char, Formula*>& substitutions) const = 0;
};

//! Composite formula

/**
 * Formula consisting of an operator and several formulas.
 */
class Composite: public Formula
{
public:
    Composite(char);

    /**
     * Sets given formula as the first unset operand from the left.
     * @param formula Formula to be set as an operand
     * @return True if all operands have been set, false otherwise
     */
    virtual bool setFirst(Formula* formula) = 0;

    /**
     * Set given formula as the last unset operand from the left.
     * @param formula Formula to be set as an operand
     * @return True if all operands have been set, false otherwise
     */
    virtual bool setLast(Formula* formula) = 0;
};

//! Trivial formula

/**
 * Trivial formula consisting of a proposition.
 */
class Trivial: public Formula
{
public:
    Trivial(char);
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool equals(Formula*) const;
    virtual bool matches(Formula*,
                         map<char, Formula*>&) const;
};

//! Binary operator compound formula

/**
 * Formula consisting of a binary operator and two operands.
 */
class Binary: public Composite
{
private:
    Formula* left = NULL;
    ///< The left operand

    Formula* right = NULL;
    ///< The right operand
public:
    Binary(char);
    virtual ~Binary();

    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool equals(Formula*) const;
    virtual bool matches(Formula*,
                         map<char, Formula*>&) const;
    virtual bool setFirst(Formula*);
    virtual bool setLast(Formula*);
};

//! Unary operator compound formula

/**
 * Formula consisting of an unary operator and an operand.
 */
class Unary: public Composite
{
private:
    Formula* operand = NULL;
    ///< The operand
public:
    Unary(char);
    virtual ~Unary();

    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual bool equals(Formula*) const;
    virtual bool matches(Formula*,
                         map<char, Formula*>&) const;
    virtual bool setFirst(Formula*);
    virtual bool setLast(Formula*);
};

#endif
