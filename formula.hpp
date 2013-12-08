#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <string>
#include <vector>

class Formula
{
protected:
    char character;
public:
    Formula(char);
    virtual std::string printInPrefix() const = 0;
    virtual std::string printInInfix() const = 0;
    virtual std::string printInPostfix() const = 0;
};

class Preposition : public Formula
{
public:
    Preposition(char);
    virtual std::string printInPrefix() const;
    virtual std::string printInInfix() const;
    virtual std::string printInPostfix() const;
};

class Operator : public Formula
{
protected:
    std::vector<Formula *> operands;
public:
    Operator(char);
    virtual std::string printInPrefix() const;
    virtual std::string printInInfix() const;
    virtual std::string printInPostfix() const;
    int addOperandFromLeft(Formula *);
    int addOperandFromRight(Formula *);
};

#endif	/* FORMULA_HPP */

