#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <string>

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
public:
    Operator(char);
    virtual std::string printInPrefix() const = 0;
    virtual std::string printInInfix() const = 0;
    virtual std::string printInPostfix() const = 0;
    virtual int addOperandFromLeft(Formula *) = 0;
    virtual int addOperandFromRight(Formula *) = 0;
};

class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL;
public:
    UnaryOperator(char);
    virtual std::string printInPrefix() const;
    virtual std::string printInInfix() const;
    virtual std::string printInPostfix() const;
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
    virtual std::string printInPrefix() const;
    virtual std::string printInInfix() const;
    virtual std::string printInPostfix() const;
    virtual int addOperandFromLeft(Formula *);
    virtual int addOperandFromRight(Formula *);
};

#endif	/* FORMULA_HPP */

