#include <iostream>

#include "formula.hpp"

using namespace std;

const map<char, Dictionary> Formula::dictionary = {
    {'-',
        {
            {ASCII, "-"},
            {WORDS, " not "},
            {TEX, " \\neg "}
        }
	},
    {'.',
        {
            {ASCII, "."},
            {WORDS, " and "},
            {TEX, " \\wedge "}
        }
	},
    {'+',
        {
            {ASCII, "+"},
            {WORDS, " or "},
            {TEX, " \\vee "}
        }
	},
    {'>',
        {
            {ASCII, ">"},
            {WORDS, " implies "},
            {TEX, " \\Rightarrow "}
        }
	},
    {'=',
        {
            {ASCII, "="},
            {WORDS, " if and only if "},
            {TEX, " \\Leftrightarrow "}
        }
	}
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

bool Proposition::matches(Formula * formula, Substitutions & substitutions)
const
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

Composite::Composite(char character) : Formula(character)
{
}

Unary::Unary(char character) : Composite(character)
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

bool Unary::equals(Formula * formula) const
{
    return character == formula->getCharacter()
            && operand->equals(((Unary *) formula)->operand);
}

bool Unary::matches(Formula * formula, Substitutions & subsitutions) const
{
    return character == formula->getCharacter()
            && operand->matches(((Unary *) formula)->operand, subsitutions);
}

bool Unary::setFirst(Formula * operand)
{
    if (this->operand == NULL)
    {
        this->operand = operand;
    }
    return true;
}

bool Unary::setLast(Formula * operand)
{
    if (this->operand == NULL)
    {
        this->operand = operand;
    }
    return true;
}

Binary::Binary(char character) : Composite(character)
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

bool Binary::equals(Formula * formula) const
{
    return character == formula->getCharacter()
            && left->equals(((Binary *) formula)->left)
            && right->equals(((Binary *) formula)->right);
}

bool Binary::matches(Formula * formula, Substitutions & substitutions) const
{
    return character == formula->getCharacter()
            && left->matches(((Binary *) formula)->left, substitutions)
            && right->matches(((Binary *) formula)->right, substitutions);
}

bool Binary::setFirst(Formula * operand)
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

bool Binary::setLast(Formula * operand)
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
