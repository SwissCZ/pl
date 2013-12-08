#include <string>

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

std::string Operator::printInPrefix() const
{
    std::string output;
    output += this->character;
    for (Formula * operand : operands)
    {
        output += operand->printInPrefix();
    }
    return output;
}

std::string Operator::printInInfix() const
{
    std::string output;
    output += '(';
    for (Formula * operand : operands)
    {
        output += operand->printInInfix();
        output += this->character;
    }
    output.pop_back();
    output += ')';
    return output;
}

std::string Operator::printInPostfix() const
{
    std::string output;
    for (Formula * operand : operands)
    {
        output += operand->printInPostfix();
    }
    output += this->character;
    return output;
}

int Operator::addOperandFromLeft(Formula * operand)
{
    this->operands.push_back(operand);
    return language.at(character).operands - operands.size();
}

int Operator::addOperandFromRight(Formula * operand)
{
    this->operands.insert(operands.begin(), operand);
    return language.at(character).operands - operands.size();
}



