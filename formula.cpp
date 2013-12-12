#include "formula.hpp"

// Formula

Formula::Formula(char character)
{
    this->character = character;
}

// Preposition

Preposition::Preposition(char name) : Formula(name)
{
}

std::string Preposition::printPrefix() const
{
    return std::string() + this->character;
}

std::string Preposition::printInfix() const
{
    return std::string() + this->character;
}

std::string Preposition::printPostfix() const
{
    return std::string() + this->character;
}

// Operator

Operator::Operator(char symbol) : Formula(symbol)
{
}

// UnaryOperator

UnaryOperator::UnaryOperator(char symbol) : Operator(symbol)
{
}

std::string UnaryOperator::printPrefix() const
{
    return std::string() + this->character + operand->printPrefix();
}

std::string UnaryOperator::printInfix() const
{
    return std::string() + '(' + this->character + operand->printInfix() + ')';
}

std::string UnaryOperator::printPostfix() const
{
    return std::string() + operand->printPostfix() + this->character;
}

int UnaryOperator::addOperandFromLeft(Formula * operand)
{
    this->operand = operand;
    return 0;
}

int UnaryOperator::addOperandFromRight(Formula * operand)
{
    return addOperandFromLeft(operand);
}

// BinaryOperator

BinaryOperator::BinaryOperator(char symbol) : Operator(symbol)
{
}

std::string BinaryOperator::printPrefix() const
{
    return std::string() + this->character + leftOperand->printPrefix() + rightOperand->printPrefix();
}

std::string BinaryOperator::printInfix() const
{
    return std::string() + '(' + leftOperand->printInfix() + this->character + rightOperand->printInfix() + ')';
}

std::string BinaryOperator::printPostfix() const
{
    return std::string() + leftOperand->printPostfix() + rightOperand->printPostfix() + this->character;
}

int BinaryOperator::addOperandFromLeft(Formula * operand)
{
    if (leftOperand == NULL)
    {
        leftOperand = operand;
        return 1;
    } else
    {
        rightOperand = operand;
        return 0;
    }
}

int BinaryOperator::addOperandFromRight(Formula * operand)
{
    if (rightOperand == NULL)
    {
        rightOperand = operand;
        return 1;
    } else
    {
        leftOperand = operand;
        return 0;
    }
}

