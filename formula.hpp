#ifndef FORMULA_HPP
#define	FORMULA_HPP

#include <string>

#include "connective.hpp"
#include "notation.hpp"

class Node {
public:
    virtual std::string print(Notation) const = 0;
};

class Preposition : public Node {
private:
    char name;
public:
    Preposition(char);
    virtual std::string print(Notation) const;
};

class Operator : public Node {
protected:
    Connective connective;
    int operandsLeft;
public:
    Operator(Connective, int);
    virtual int addOperand(Node *) = 0;
};

class UnaryOperator : public Operator {
private:
    Node * operand = NULL;
public:
    UnaryOperator(Connective);
    virtual std::string print(Notation) const;
    virtual int addOperand(Node *);
};

class BinaryOperator : public Operator {
private:
    Node * operand1 = NULL;
    Node * operand2 = NULL;
public:
    BinaryOperator(Connective);
    virtual std::string print(Notation) const;
    virtual int addOperand(Node *);
};

#endif	/* FORMULA_HPP */

