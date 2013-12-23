#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <string>

class Formula
{
protected:
    char character;
public:
    Formula(const char &);
    virtual ~Formula();
    virtual std::string printPrefix() const = 0;
    virtual std::string printInfix() const = 0;
    virtual std::string printPostfix() const = 0;
};

class Proposition : public Formula
{
public:
    Proposition(const char &);
    virtual ~Proposition();
    virtual std::string printPrefix() const;
    virtual std::string printInfix() const;
    virtual std::string printPostfix() const;
};

class Operator : public Formula
{
public:
    Operator(const char &);
    virtual ~Operator();
    virtual std::string printPrefix() const = 0;
    virtual std::string printInfix() const = 0;
    virtual std::string printPostfix() const = 0;
    virtual int addOperandRightwards(Formula *) = 0;
    virtual int addOperandLeftwards(Formula *) = 0;
};

class UnaryOperator : public Operator
{
private:
    Formula * operand = NULL;
public:
    UnaryOperator(const char &);
    virtual ~UnaryOperator();
    virtual std::string printPrefix() const;
    virtual std::string printInfix() const;
    virtual std::string printPostfix() const;
    virtual int addOperandRightwards(Formula *);
    virtual int addOperandLeftwards(Formula *);
};

class BinaryOperator : public Operator
{
private:
    Formula * leftOperand = NULL;
    Formula * rightOperand = NULL;
public:
    BinaryOperator(const char &);
    virtual ~BinaryOperator();
    virtual std::string printPrefix() const;
    virtual std::string printInfix() const;
    virtual std::string printPostfix() const;
    virtual int addOperandRightwards(Formula *);
    virtual int addOperandLeftwards(Formula *);
};

#endif	/* FORMULA_HPP */

