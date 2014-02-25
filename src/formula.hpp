#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <string>

#include "connective.hpp"
#include "language.hpp"

using namespace std;

class Formula
{
public:
    Formula();
    virtual ~Formula();
    virtual string printPrefix(Language) const = 0;
    virtual string printInfix(Language) const = 0;
    virtual string printPostfix(Language) const = 0;
};

class Proposition : public Formula
{
private:
    char character;
public:
    Proposition(char &);
    virtual ~Proposition();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
};

class Operator : public Formula
{
protected:
    Connective connective;
public:
    Operator(Connective);
    virtual ~Operator();
    virtual string printPrefix(Language) const = 0;
    virtual string printInfix(Language) const = 0;
    virtual string printPostfix(Language) const = 0;
    virtual int appendFirst(Formula *) = 0;
    virtual int appendLast(Formula *) = 0;
};

class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL;
public:
    UnaryOperator(Connective);
    virtual ~UnaryOperator();
    virtual string printPrefix(Language) const;
    virtual string printInfix(Language) const;
    virtual string printPostfix(Language) const;
    virtual int appendFirst(Formula *);
    virtual int appendLast(Formula *);
};

class BinaryOperator : public Operator
{
private:
    Formula * left_operand = NULL;
    Formula * right_operand = NULL;
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
