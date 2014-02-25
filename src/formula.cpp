#include "formula.hpp"
#include "language_resource.hpp"

Formula::Formula()
{
}

Formula::~Formula()
{
}

Proposition::Proposition(char & character) : Formula()
{
    this->character = character;
}

Proposition::~Proposition()
{
}

std::string Proposition::printPrefix(Language & language) const
{
    return std::string() + this->character;
}

std::string Proposition::printInfix(Language & language) const
{
    return std::string() + this->character;
}

std::string Proposition::printPostfix(Language & language) const
{
    return std::string() + this->character;
}

Operator::Operator(Connective connective) : Formula()
{
    this->connective = connective;
}

Operator::~Operator()
{
}

UnaryOperator::UnaryOperator(Connective connective) : Operator(connective)
{
}

UnaryOperator::~UnaryOperator()
{
    delete operand;
}

std::string UnaryOperator::printPrefix(Language & language) const
{
    return std::string() + RESOURCE.at(connective).at(language) + operand->printPrefix(language);
}

std::string UnaryOperator::printInfix(Language & language) const
{
    return std::string() + RESOURCE.at(connective).at(language) + operand->printInfix(language);
}

std::string UnaryOperator::printPostfix(Language & language) const
{
    return std::string() + operand->printPostfix(language) + RESOURCE.at(connective).at(language);
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

BinaryOperator::BinaryOperator(Connective connective) : Operator(connective)
{
}

BinaryOperator::~BinaryOperator()
{
    delete leftOperand;
    delete rightOperand;
}

std::string BinaryOperator::printPrefix(Language & language) const
{
    return std::string() + RESOURCE.at(connective).at(language) + leftOperand->printPrefix(language) + rightOperand->printPrefix(language);
}

std::string BinaryOperator::printInfix(Language & language) const
{
    return std::string() + '(' + leftOperand->printInfix(language) + RESOURCE.at(connective).at(language) + rightOperand->printInfix(language) + ')';
}

std::string BinaryOperator::printPostfix(Language & language) const
{
    return std::string() + leftOperand->printPostfix(language) + rightOperand->printPostfix(language) + RESOURCE.at(connective).at(language);
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

