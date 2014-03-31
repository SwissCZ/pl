#include "formula.hpp"

using namespace std;

map<char, Dictionary> Formula::dictionary = {
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

bool Proposition::matchesFormula(Formula * formula) const
{
    return this->character == formula->getCharacter();
}

bool Proposition::matchesSubstitutions(Formula * formula,
                                       Substitutions * substitutions) const
{
    try
    {
        return substitutions->at(character)->matchesFormula(formula);
    } catch (out_of_range & ex)
    {
        substitutions->emplace(character, formula);
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

bool UnaryOperator::matchesFormula(Formula * formula) const
{
    return character == formula->getCharacter()
            && operand->matchesFormula(((UnaryOperator *) formula)->operand);
}

bool UnaryOperator::matchesSubstitutions(Formula * formula,
                                         Substitutions * subsitutions) const
{
    return character == formula->getCharacter() && operand->matchesSubstitutions
            (((UnaryOperator *) formula)->operand, subsitutions);
}

int UnaryOperator::append(Formula * operand)
{
    this->operand = operand;
    return 0;
}

int UnaryOperator::insert(Formula * operand)
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

bool BinaryOperator::matchesFormula(Formula * formula) const
{
    return character == formula->getCharacter()
            && left->matchesFormula
            (((BinaryOperator *) formula)->left)
            && right->matchesFormula
            (((BinaryOperator *) formula)->right);
}

bool BinaryOperator::matchesSubstitutions(Formula * formula,
                                          Substitutions * substitutions)
const
{
    return character == formula->getCharacter()
            && left->matchesSubstitutions
            (((BinaryOperator *) formula)->left, substitutions)
            && right->matchesSubstitutions
            (((BinaryOperator *) formula)->right, substitutions);
}

int BinaryOperator::append(Formula * operand)
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

int BinaryOperator::insert(Formula * operand)
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
