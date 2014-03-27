#include "formula.hpp"

using namespace std;

map<char, LanguageMap> Formula::INPUT_LANGUAGE = {
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
                                       SubstituteMap * substitutions) const
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
            + INPUT_LANGUAGE.at(character).at(language)
            + operand->printPrefix(language);
}

string UnaryOperator::printInfix(Language language) const
{
    return string()
            + INPUT_LANGUAGE.at(character).at(language)
            + operand->printInfix(language);
}

string UnaryOperator::printPostfix(Language language) const
{
    return string()
            + operand->printPostfix(language)
            + INPUT_LANGUAGE.at(character).at(language);
}

bool UnaryOperator::matchesFormula(Formula * formula) const
{
    return character == formula->getCharacter()
            && operand->matchesFormula(((UnaryOperator *) formula)->operand);
}

bool UnaryOperator::matchesSubstitutions(Formula * formula,
                                         SubstituteMap * subsitutions) const
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
    delete leftOperand;
    delete rightOperand;
}

string BinaryOperator::printPrefix(Language language) const
{
    return string()
            + INPUT_LANGUAGE.at(character).at(language)
            + leftOperand->printPrefix(language)
            + rightOperand->printPrefix(language);
}

string BinaryOperator::printInfix(Language language) const
{
    return string()
            + '('
            + leftOperand->printInfix(language)
            + INPUT_LANGUAGE.at(character).at(language)
            + rightOperand->printInfix(language)
            + ')';
}

string BinaryOperator::printPostfix(Language language) const
{
    return string()
            + leftOperand->printPostfix(language)
            + rightOperand->printPostfix(language)
            + INPUT_LANGUAGE.at(character).at(language);
}

bool BinaryOperator::matchesFormula(Formula * formula) const
{
    return character == formula->getCharacter()
            && leftOperand->matchesFormula
            (((BinaryOperator *) formula)->leftOperand)
            && rightOperand->matchesFormula
            (((BinaryOperator *) formula)->rightOperand);
}

bool BinaryOperator::matchesSubstitutions(Formula* formula,
                                          SubstituteMap * substitutions)
const
{
    return character == formula->getCharacter()
            && leftOperand->matchesSubstitutions
            (((BinaryOperator *) formula)->leftOperand, substitutions)
            && rightOperand->matchesSubstitutions
            (((BinaryOperator *) formula)->rightOperand, substitutions);
}

int BinaryOperator::append(Formula * operand)
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

int BinaryOperator::insert(Formula * operand)
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
