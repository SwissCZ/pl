#include <cstdio>
#include <ctype.h>
#include <stack>
#include <iostream>

#include "formula.hpp"

using namespace std;

Preposition::Preposition(char name) {
    this->name = name;
}

std::string Preposition::print(Notation notation) const {
    std::string retval;
    retval = name;
    return retval;
}

Operator::Operator(Connective connective, int operandsLeft) {
    cout << (char)connective << endl;
    this->connective = connective;
    this->operandsLeft = operandsLeft;
}

UnaryOperator::UnaryOperator(Connective connective) : Operator(connective, 1) {
}

std::string UnaryOperator::print(Notation notation) const {
    std::string retval;
    switch (notation) {
        case PREFIX:
            retval += this->connective;
            retval += this->operand->print(notation);
            break;
        case INFIX:
            retval += this->connective;
            retval += this->operand->print(notation);
            break;
        case POSTFIX:
            retval += this->operand->print(notation);
            retval += this->connective;
            break;
    }
    return retval;
}

int UnaryOperator::addOperand(Node * operand) {
    if (this->operand == NULL) {
        this->operand = operand;
    } else {
        // syntax error
    }
    return --operandsLeft;
}

BinaryOperator::BinaryOperator(Connective connective) : Operator(connective, 2) {
}

std::string BinaryOperator::print(Notation notation) const {
    std::string retval;
    switch (notation) {
        case PREFIX:
            retval += this->connective;
            retval += this->operand1->print(notation);
            retval += this->operand2->print(notation);
            break;
        case INFIX:
            retval += '(';
            retval += this->operand1->print(notation);
            retval += this->connective;
            retval += this->operand2->print(notation);
            retval += ')';
            break;
        case POSTFIX:
            retval += this->operand1->print(notation);
            retval += this->operand2->print(notation);
            retval += this->connective;
            break;
    }
    return retval;
}

int BinaryOperator::addOperand(Node * operand) {
    if (this->operand1 == NULL) {
        this->operand1 = operand;
    } else if (this->operand2 == NULL) {
        this->operand2 = operand;
    } else {
        // syntax error
    }
    return --operandsLeft;
}

