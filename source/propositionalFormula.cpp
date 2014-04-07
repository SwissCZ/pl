#include "propositionalFormula.hpp"

using namespace std;

map<char, Dictionary> PropositionalFormula::dictionary = {
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

PropositionalFormula::PropositionalFormula(char character) : character(character)
{
}

PropositionalFormula::~PropositionalFormula()
{
}

char PropositionalFormula::getCharacter() const
{
    return character;
}

Proposition::Proposition(char character) : PropositionalFormula(character)
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

bool Proposition::matchesFormula(PropositionalFormula * formula) const
{
    return this->character == formula->getCharacter();
}

bool Proposition::matchesAxiom(PropositionalFormula * formula,
                                       Substitutions & substitutions) const
{
    try
    {
        return substitutions.at(character)->matchesFormula(formula);
    } catch (out_of_range & ex)
    {
        substitutions.emplace(character, formula);
        return true;
    }
}

Operator::Operator(char character) : PropositionalFormula(character)
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
    return string()
            + dictionary.at(character).at(language)
            + operand->printPrefix(language);
}

string UnaryOperator::printInfix(Language language) const
{
    return string()
            + dictionary.at(character).at(language)
            + operand->printInfix(language);
}

string UnaryOperator::printPostfix(Language language) const
{
    return string()
            + operand->printPostfix(language)
            + dictionary.at(character).at(language);
}

bool UnaryOperator::matchesFormula(PropositionalFormula * formula) const
{
    return character == formula->getCharacter()
            && operand->matchesFormula(((UnaryOperator *) formula)->operand);
}

bool UnaryOperator::matchesAxiom(PropositionalFormula * formula,
                                         Substitutions & subsitutions) const
{
    return character == formula->getCharacter() && operand->matchesAxiom
            (((UnaryOperator *) formula)->operand, subsitutions);
}

int UnaryOperator::append(PropositionalFormula * operand)
{
    this->operand = operand;
    return 0;
}

int UnaryOperator::insert(PropositionalFormula * operand)
{
    return append(operand);
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
    return string()
            + dictionary.at(character).at(language)
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
    return string()
            + left->printPostfix(language)
            + right->printPostfix(language)
            + dictionary.at(character).at(language);
}

bool BinaryOperator::matchesFormula(PropositionalFormula * formula) const
{
    return character == formula->getCharacter()
            && left->matchesFormula
            (((BinaryOperator *) formula)->left)
            && right->matchesFormula
            (((BinaryOperator *) formula)->right);
}

bool BinaryOperator::matchesAxiom(PropositionalFormula * formula,
                                          Substitutions & substitutions)
const
{
    return character == formula->getCharacter()
            && left->matchesAxiom
            (((BinaryOperator *) formula)->left, substitutions)
            && right->matchesAxiom
            (((BinaryOperator *) formula)->right, substitutions);
}

int BinaryOperator::append(PropositionalFormula * operand)
{
    if (left == NULL)
    {
        left = operand;
        return 1;
    } else
    {
        right = operand;
        return 0;
    }
}

int BinaryOperator::insert(PropositionalFormula * operand)
{
    if (right == NULL)
    {
        right = operand;
        return 1;
    } else
    {
        left = operand;
        return 0;
    }
}
