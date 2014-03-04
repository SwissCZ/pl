#include "formula.hpp"

Formula::~Formula()
{

}

Proposition::Proposition(char character) : Formula()
{
    this->character = character;
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

Operator::Operator(Connective operation) : Formula()
{
    this->operation = operation;
}

UnaryOperator::UnaryOperator(Connective operation) : Operator(operation)
{
}

UnaryOperator::~UnaryOperator()
{
    delete operand;
}

std::string UnaryOperator::printPrefix(Language language) const
{
    return std::string()
            + languageMap.at(operation).at(language)
            + operand->printPrefix(language);
}

std::string UnaryOperator::printInfix(Language language) const
{
    return std::string()
            + languageMap.at(operation).at(language)
            + operand->printInfix(language);
}

std::string UnaryOperator::printPostfix(Language language) const
{
    return std::string()
            + operand->printPostfix(language)
            + languageMap.at(operation).at(language);
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

BinaryOperator::BinaryOperator(Connective operation) : Operator(operation)
{
}

BinaryOperator::~BinaryOperator()
{
    delete leftOperand;
    delete rightOperand;
}

std::string BinaryOperator::printPrefix(Language language) const
{
    return std::string()
            + languageMap.at(operation).at(language)
            + leftOperand->printPrefix(language)
            + rightOperand->printPrefix(language);
}

std::string BinaryOperator::printInfix(Language language) const
{
    return std::string()
            + '('
            + leftOperand->printInfix(language)
            + languageMap.at(operation).at(language)
            + rightOperand->printInfix(language)
            + ')';
}

std::string BinaryOperator::printPostfix(Language language) const
{
    return std::string()
            + leftOperand->printPostfix(language)
            + rightOperand->printPostfix(language)
            + languageMap.at(operation).at(language);
}

int BinaryOperator::appendFirst(Formula * operand)
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

int BinaryOperator::appendLast(Formula * operand)
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
