#ifndef LANGUAGE_HPP
#define	LANGUAGE_HPP

#include <map>

#define NEGATION_CHAR '-'
#define CONJUNCTION_CHAR '*'
#define DISJUNCTION_CHAR '+'
#define IMPLICATION_CHAR '>'
#define EQUIVALENCE_CHAR '='

#define NEGATION_WORD "not"
#define CONJUNCTION_WORD "and"
#define DISJUNCTION_WORD "or"
#define IMPLICATION_WORD "implies"
#define EQUIVALENCE_WORD "iff"

#define NEGATION_TEX "\\neg"
#define CONJUNCTION_TEX "\\wedge"
#define DISJUNCTION_TEX "\\vee"
#define IMPLICATION_TEX "\\rigtharrow"
#define EQUIVALENCE_TEX "\\leftrightarrow"

struct Connective
{
    const int operands;
    const char * word;
    const char * tex;
};

const std::map<char, Connective> language = {
    {NEGATION_CHAR,
        {1, NEGATION_WORD, NEGATION_TEX}},
    {CONJUNCTION_CHAR,
        {2, CONJUNCTION_WORD, CONJUNCTION_TEX}},
    {DISJUNCTION_CHAR,
        {2, DISJUNCTION_WORD, DISJUNCTION_TEX}},
    {IMPLICATION_CHAR,
        {2, IMPLICATION_WORD, IMPLICATION_TEX}},
    {EQUIVALENCE_CHAR,
        {2, EQUIVALENCE_WORD, EQUIVALENCE_TEX}}
};

#endif	/* LANGUAGE_HPP */

