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

std::string Preposition::printPrefix() const
{
    std::string output;
    output += character;
    return output;
}

std::string Preposition::printInfix() const
{
    std::string output;
    output += character;
    return output;
}

std::string Preposition::printPostfix() const
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

std::string UnaryOperator::printPrefix() const
{
    std::string output;
    output += this->character + operand->printPrefix();
    return output;
}

std::string UnaryOperator::printInfix() const
{
    std::string output;
    output += '(' + std::string(1, this->character) + operand->printInfix() + ')';
    return output;
}

std::string UnaryOperator::printPostfix() const
{
    std::string output;
    output += operand->printPostfix() + this->character;
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

std::string BinaryOperator::printPrefix() const
{
    std::string output;
    output += this->character + leftOperand->printPrefix() + rightOperand->printPrefix();
    return output;
}

std::string BinaryOperator::printInfix() const
{
    std::string output;
    output += '(' + leftOperand->printInfix() + this->character + rightOperand->printInfix() + ')';
    return output;
}

std::string BinaryOperator::printPostfix() const
{
    std::string output;
    output += leftOperand->printPostfix() + rightOperand->printPostfix() + this->character;
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

