#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <string>

class Formula
{
protected:
    char character;
public:
    Formula(char);
    virtual std::string printPrefix() const = 0;
    virtual std::string printInfix() const = 0;
    virtual std::string printPostfix() const = 0;
};

class Preposition : public Formula
{
public:
    Preposition(char);
    virtual std::string printPrefix() const;
    virtual std::string printInfix() const;
    virtual std::string printPostfix() const;
};

class Operator : public Formula
{
public:
    Operator(char);
    virtual std::string printPrefix() const = 0;
    virtual std::string printInfix() const = 0;
    virtual std::string printPostfix() const = 0;
    virtual int addOperandFromLeft(Formula *) = 0;
    virtual int addOperandFromRight(Formula *) = 0;
};

class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL;
public:
    UnaryOperator(char);
    virtual std::string printPrefix() const;
    virtual std::string printInfix() const;
    virtual std::string printPostfix() const;
    virtual int addOperandFromLeft(Formula *);
    virtual int addOperandFromRight(Formula *);
};

class BinaryOperator : public Operator
{
private:
    Formula * leftOperand = NULL;
    Formula * rightOperand = NULL;
public:
    BinaryOperator(char);
    virtual std::string printPrefix() const;
    virtual std::string printInfix() const;
    virtual std::string printPostfix() const;
    virtual int addOperandFromLeft(Formula *);
    virtual int addOperandFromRight(Formula *);
};

#endif	/* FORMULA_HPP */

