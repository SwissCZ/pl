#include "formula.hpp"
#include "language_definition.hpp"

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

std::string Proposition::printPrefix(Language language) const
{
    return std::string() + this->character;
}

std::string Proposition::printInfix(Language language) const
{
    return std::string() + this->character;
}

std::string Proposition::printPostfix(Language language) const
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

std::string UnaryOperator::printPrefix(Language language) const
{
    return std::string() + language_map.at(connective).at(language) + operand->printPrefix(language);
}

std::string UnaryOperator::printInfix(Language language) const
{
    return std::string() + language_map.at(connective).at(language) + operand->printInfix(language);
}

std::string UnaryOperator::printPostfix(Language language) const
{
    return std::string() + operand->printPostfix(language) + language_map.at(connective).at(language);
}

int UnaryOperator::appendFirst(Formula * operand)
{
    this->operand = operand;
    return 0;
}

int UnaryOperator::appendLast(Formula * operand)
{
    return appendFirst(operand);
}

BinaryOperator::BinaryOperator(Connective connective) : Operator(connective)
{
}

BinaryOperator::~BinaryOperator()
{
    delete left_operand;
    delete right_operand;
}

std::string BinaryOperator::printPrefix(Language language) const
{
    return std::string() + language_map.at(connective).at(language) + left_operand->printPrefix(language) + right_operand->printPrefix(language);
}

std::string BinaryOperator::printInfix(Language language) const
{
    return std::string() + '(' + left_operand->printInfix(language) + language_map.at(connective).at(language) + right_operand->printInfix(language) + ')';
}

std::string BinaryOperator::printPostfix(Language language) const
{
    return std::string() + left_operand->printPostfix(language) + right_operand->printPostfix(language) + language_map.at(connective).at(language);
}

int BinaryOperator::appendFirst(Formula * operand)
{
    if (left_operand == NULL)
    {
        left_operand = operand;
        return 1;
    } else
    {
        right_operand = operand;
        return 0;
    }
}

int BinaryOperator::appendLast(Formula * operand)
{
    if (right_operand == NULL)
    {
        right_operand = operand;
        return 1;
    } else
    {
        left_operand = operand;
        return 0;
    }
}

