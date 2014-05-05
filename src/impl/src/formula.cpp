#include "formula.hpp"

#include <iostream>

using namespace std;

const map<char, Dictionary> Formula::dictionary = {
    {'-',
        {
            {ASCII, "-"},
            {WORDS, " not "},
            {TEX, "\\neg"}
        }},
    {'.',
        {
            {ASCII, "."},
            {WORDS, " and "},
            {TEX, "\\wedge"}
        }},
    {'+',
        {
            {ASCII, "+"},
            {WORDS, " or "},
            {TEX, "\\vee"}
        }},
    {'>',
        {
            {ASCII, ">"},
            {WORDS, " implies "},
            {TEX, "\\rightarrow"}
        }},
    {'=',
        {
            {ASCII, "="},
            {WORDS, " iff "},
            {TEX, "\\leftrightarrow"}
        }}
};

Formula::Formula(char character) : character(character)
{
}

Formula::~Formula()
{
}

char Formula::getCharacter() const
{
    return character;
}

Proposition::Proposition(char character) : Formula(character)
{
}

string Proposition::printPrefix(Language language) const
{
    return string() + this->character;
}

string Proposition::printInfix(Language language) const
{
    return string() + this->character;
}

string Proposition::printPostfix(Language language) const
{
    return string() + this->character;
}

bool Proposition::equals(Formula * formula) const
{
    return this->character == formula->getCharacter();
}

bool Proposition::matches(Formula * formula, Substitutions & substitutions) const
{
    try
    {
        return substitutions.at(character)->equals(formula);
    } catch (out_of_range & ex)
    {
        substitutions.emplace(character, formula);
        return true;
    }
}

Operator::Operator(char character) : Formula(character)
{
}

UnaryOperator::UnaryOperator(char character) : Operator(character)
{
}

UnaryOperator::~UnaryOperator()
{
    delete operand;
}

string UnaryOperator::printPrefix(Language language) const
{
    return dictionary.at(character).at(language)
            + operand->printPrefix(language);
}

string UnaryOperator::printInfix(Language language) const
{
    return dictionary.at(character).at(language)
            + operand->printInfix(language);
}

string UnaryOperator::printPostfix(Language language) const
{
    return operand->printPostfix(language)
            + dictionary.at(character).at(language);
}

bool UnaryOperator::equals(Formula * formula) const
{
    return character == formula->getCharacter()
            && operand->equals(((UnaryOperator *) formula)->operand);
}

bool UnaryOperator::matches(Formula * formula, Substitutions & subsitutions) const
{
    return character == formula->getCharacter()
            && operand->matches(((UnaryOperator *) formula)->operand, subsitutions);
}

bool UnaryOperator::append(Formula * operand)
{
    if (this->operand == NULL)
    {
        this->operand = operand;
    }
    return true;
}

bool UnaryOperator::insert(Formula * operand)
{
    if (this->operand == NULL)
    {
        this->operand = operand;
    }
    return true;
}

BinaryOperator::BinaryOperator(char character) : Operator(character)
{
}

BinaryOperator::~BinaryOperator()
{
    delete left;
    delete right;
}

string BinaryOperator::printPrefix(Language language) const
{
    return dictionary.at(character).at(language)
            + left->printPrefix(language)
            + right->printPrefix(language);
}

string BinaryOperator::printInfix(Language language) const
{
    return string()
            + '('
            + left->printInfix(language)
            + dictionary.at(character).at(language)
            + right->printInfix(language)
            + ')';
}

string BinaryOperator::printPostfix(Language language) const
{
    return left->printPostfix(language)
            + right->printPostfix(language)
            + dictionary.at(character).at(language);
}

bool BinaryOperator::equals(Formula * formula) const
{
    return character == formula->getCharacter()
            && left->equals(((BinaryOperator *) formula)->left)
            && right->equals(((BinaryOperator *) formula)->right);
}

bool BinaryOperator::matches(Formula * formula, Substitutions & substitutions) const
{
    return character == formula->getCharacter()
            && left->matches(((BinaryOperator *) formula)->left, substitutions)
            && right->matches(((BinaryOperator *) formula)->right, substitutions);
}

bool BinaryOperator::append(Formula * operand)
{
    if (left == NULL)
    {
        left = operand;
        return false;
    } else if (right == NULL)
    {
        right = operand;
    }
    return true;
}

bool BinaryOperator::insert(Formula * operand)
{
    if (right == NULL)
    {
        right = operand;
        return false;
    } else if (left == NULL)
    {
        left = operand;
    }
    return true;
}
