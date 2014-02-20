#include "formula.hpp"

// Formula

Formula::Formula(const char & character)
{
    this->character = character;
}

Formula::~Formula()
{
}

// Proposition

Proposition::Proposition(const char & name) : Formula(name)
{
}

Proposition::~Proposition()
{
}

std::string Proposition::printPrefix() const
{
    return std::string() + this->character;
}

std::string Proposition::printInfix() const
{
    return std::string() + this->character;
}

std::string Proposition::printPostfix() const
{
    return std::string() + this->character;
}

// Operator

Operator::Operator(const char & symbol) : Formula(symbol)
{
}

Operator::~Operator()
{
}

// UnaryOperator

UnaryOperator::UnaryOperator(const char & symbol) : Operator(symbol)
{
}

UnaryOperator::~UnaryOperator()
{
    delete operand;
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

int UnaryOperator::addOperandRightwards(Formula * operand)
{
    this->operand = operand;
    return 0;
}

int UnaryOperator::addOperandLeftwards(Formula * operand)
{
    return addOperandRightwards(operand);
}

// BinaryOperator

BinaryOperator::BinaryOperator(const char & symbol) : Operator(symbol)
{
}

BinaryOperator::~BinaryOperator()
{
    delete leftOperand;
    delete rightOperand;
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

int BinaryOperator::addOperandRightwards(Formula * operand)
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

int BinaryOperator::addOperandLeftwards(Formula * operand)
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

