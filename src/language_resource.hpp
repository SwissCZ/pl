#ifndef LANGUAGE_RESOURCE_HPP
#define	LANGUAGE_RESOURCE_HPP

#include <map>

#include "connective.hpp"
#include "language.hpp"

const std::map<Connective, std::map<Language, const char * >> RESOURCE = {
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

#endif	/* LANGUAGE_RESOURCE_HPP */

