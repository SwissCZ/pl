#include "formula.hpp"
#include "language.hpp"

// Formula

Formula::Formula(char character)
{
    this->character = character;
}

// Preposition

Preposition::Preposition(char name) : Formula(name)
{
}

std::string Preposition::printInPrefix() const
{
    std::string output;
    output += character;
    return output;
}

std::string Preposition::printInInfix() const
{
    std::string output;
    output += character;
    return output;
}

std::string Preposition::printInPostfix() const
{
    std::string output;
    output += character;
    return output;
}

// Operator

Operator::Operator(char symbol) : Formula(symbol)
{
}

// UnaryOperator

UnaryOperator::UnaryOperator(char symbol) : Operator(symbol)
{
}

std::string UnaryOperator::printInPrefix() const
{
    std::string output;
    output += this->character + operand->printInPrefix();
    return output;
}

std::string UnaryOperator::printInInfix() const
{
    return printInPrefix();
}

std::string UnaryOperator::printInPostfix() const
{
    std::string output;
    output += operand->printInPostfix() + this->character;
    return output;
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

std::string BinaryOperator::printInPrefix() const
{
    std::string output;
    output += this->character + leftOperand->printInPrefix() + leftOperand->printInPrefix();
    return output;
}

std::string BinaryOperator::printInInfix() const
{
    std::string output;
    output += '(' + leftOperand->printInInfix() + this->character + rightOperand->printInInfix() + ')';
    return output;
}

std::string BinaryOperator::printInPostfix() const
{
    std::string output;
    output += leftOperand->printInPostfix() + rightOperand->printInPostfix() + this->character;
    return output;
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

