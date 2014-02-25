#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <string>

#include "connective.hpp"
#include "language.hpp"

class Formula
{
public:
    Formula();
    virtual ~Formula();
    virtual std::string printPrefix(Language &) const = 0;
    virtual std::string printInfix(Language &) const = 0;
    virtual std::string printPostfix(Language &) const = 0;
};

class Proposition : public Formula
{
private:
    char character;
public:
    Proposition(char &);
    virtual ~Proposition();
    virtual std::string printPrefix(Language &) const;
    virtual std::string printInfix(Language &) const;
    virtual std::string printPostfix(Language &) const;
};

class Operator : public Formula
{
protected:
    Connective connective;
public:
    Operator(Connective);
    virtual ~Operator();
    virtual std::string printPrefix(Language &) const = 0;
    virtual std::string printInfix(Language &) const = 0;
    virtual std::string printPostfix(Language &) const = 0;
    virtual int addOperandRightwards(Formula *) = 0;
    virtual int addOperandLeftwards(Formula *) = 0;
};

class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL;
public:
    UnaryOperator(Connective);
    virtual ~UnaryOperator();
    virtual std::string printPrefix(Language &) const;
    virtual std::string printInfix(Language &) const;
    virtual std::string printPostfix(Language &) const;
    virtual int addOperandRightwards(Formula *);
    virtual int addOperandLeftwards(Formula *);
};

class BinaryOperator : public Operator
{
private:
    Formula * leftOperand = NULL;
    Formula * rightOperand = NULL;
public:
    BinaryOperator(Connective);
    virtual ~BinaryOperator();
    virtual std::string printPrefix(Language &) const;
    virtual std::string printInfix(Language &) const;
    virtual std::string printPostfix(Language &) const;
    virtual int addOperandRightwards(Formula *);
    virtual int addOperandLeftwards(Formula *);
};

#endif	/* FORMULA_HPP */

