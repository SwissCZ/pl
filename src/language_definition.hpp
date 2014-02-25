#ifndef LANGUAGE_DEFINITION_HPP
#define	LANGUAGE_DEFINITION_HPP

#include <map>

#include "connective.hpp"
#include "language.hpp"

using namespace std;

const map<Connective, std::map<Language, const char * >> language_map = {
    {NEGATION,
        {
            {ASCII, "-"},
            {COMMON, " not "},
            {TEX, "\\neg"}
        }},
    {CONJUNCTION,
        {
            {ASCII, "."},
            {COMMON, " and "},
            {TEX, "\\wedge"}
        }},
    {DISJUNCTION,
        {
            {ASCII, "+"},
            {COMMON, " or "},
            {TEX, "\\vee"}
        }},
    {IMPLICATION,
        {
            {ASCII, ">"},
            {COMMON, " implies "},
            {TEX, "\\rightarrow"}
        }},
    {EQUIVALENCE,
        {
            {ASCII, "="},
            {COMMON, " is "},
            {TEX, "\\leftrightarrow"}
        }}
};

#endif	/* LANGUAGE_DEFINITION_HPP */
