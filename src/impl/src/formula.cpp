#include <iostream>
#include <stdexcept>

#include "formula.hpp"

map<char, map<Language, string>> Formula::dictionary = {
    {'-',
        {
            {ASCII, "-"},
            {WORDS, " not "},
            {LATEX, " \\neg "}
        }},
    {'.',
        {
            {ASCII, "."},
            {WORDS, " and "},
            {LATEX, " \\wedge "}
        }},
    {'+',
        {
            {ASCII, "+"},
            {WORDS, " or "},
            {LATEX, " \\vee "}
        }},
    {'>',
        {
            {ASCII, ">"},
            {WORDS, " implies "},
            {LATEX, " \\Rightarrow "}
        }},
    {'=',
        {
            {ASCII, "="},
            {WORDS, " iff "},
            {LATEX, " \\Leftrightarrow "}
        }}
};

Formula::Formula(char character)
: character(character)
{
}

Formula::~Formula()
{
}

char Formula::getCharacter() const
{
    return character;
}

Composite::Composite(char character)
: Formula(character)
{
}

Trivial::Trivial(char character)
: Formula(character)
{
}

string Trivial::printPrefix(Language language) const
{
    return string() + this->character;
}

string Trivial::printInfix(Language language) const
{
    return string() + this->character;
}

string Trivial::printPostfix(Language language) const
{
    return string() + this->character;
}

bool Trivial::equals(Formula* formula) const
{
    return this->character == formula->getCharacter();
}

bool Trivial::matches(Formula* formula,
                      map<char, Formula*>& substitutions) const
{
    try
    {
        return substitutions.at(character)->equals(formula);
    } catch (out_of_range& exception)
    {
        substitutions.emplace(character, formula);
        return true;
    }
}

Binary::Binary(char character)
: Composite(character)
{
}

Binary::~Binary()
{
    delete left;
    delete right;
}

string Binary::printPrefix(Language language) const
{
    return dictionary.at(character).at(language)
            + left->printPrefix(language)
            + right->printPrefix(language);
}

string Binary::printInfix(Language language) const
{
    return string()
            + '('
            + left->printInfix(language)
            + dictionary.at(character).at(language)
            + right->printInfix(language)
            + ')';
}

string Binary::printPostfix(Language language) const
{
    return left->printPostfix(language)
            + right->printPostfix(language)
            + dictionary.at(character).at(language);
}

bool Binary::equals(Formula* formula) const
{
    return character == formula->getCharacter()
            && left->equals(((Binary*) formula)->left)
            && right->equals(((Binary*) formula)->right);
}

bool Binary::matches(Formula* formula,
                     map<char, Formula*>& substitutions) const
{
    return character == formula->getCharacter()
            && left->matches(((Binary*) formula)->left, substitutions)
            && right->matches(((Binary*) formula)->right, substitutions);
}

bool Binary::setFirst(Formula* operand)
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

bool Binary::setLast(Formula* operand)
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

Unary::Unary(char character)
: Composite(character)
{
}

Unary::~Unary()
{
    delete operand;
}

string Unary::printPrefix(Language language) const
{
    return dictionary.at(character).at(language)
            + operand->printPrefix(language);
}

string Unary::printInfix(Language language) const
{
    return dictionary.at(character).at(language)
            + operand->printInfix(language);
}

string Unary::printPostfix(Language language) const
{
    return operand->printPostfix(language)
            + dictionary.at(character).at(language);
}

bool Unary::equals(Formula* formula) const
{
    return character == formula->getCharacter()
            && operand->equals(((Unary*) formula)->operand);
}

bool Unary::matches(Formula* formula,
                    map<char, Formula*>& subsitutions) const
{
    return character == formula->getCharacter()
            && operand->matches(((Unary*) formula)->operand, subsitutions);
}

bool Unary::setFirst(Formula* operand)
{
    if (this->operand == NULL)
    {
        this->operand = operand;
    }
    return true;
}

bool Unary::setLast(Formula* operand)
{
    if (this->operand == NULL)
    {
        this->operand = operand;
    }
    return true;
}
