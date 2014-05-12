#include <stdexcept>
#include <unistd.h>

#include "configuration.hpp"
#include "syntaxException.hpp"
#include "target.hpp"

using namespace std;

const map<string, Parser> Configuration::inputSyntax = {
    {"prefix", &parsePrefix},
    {"infix", &parseInfix},
    {"postfix", &parsePostfix}
};
const map<string, Printer> Configuration::outputSyntax = {
    {"prefix", &Formula::printPrefix},
    {"infix", &Formula::printInfix},
    {"postfix", &Formula::printPostfix}
};
const map<string, Language> Configuration::outputLanguage = {
    {"ascii", ASCII},
    {"words", WORDS},
    {"tex", TEX}
};

Configuration::Configuration(int argc, char ** argv)
{
    int option;

    while ((option = getopt(argc, argv, ":ADef:i:l:o:Ps")) != -1)
    {
        switch (option)
        {
            case 'A':
                if (target == NULL)
                {
                    target = &executeAxiomCheck;
                } else
                {
                    throw MultipleTargetsException(option);
                }
                break;
            case 'D':
                if (target == NULL)
                {
                    target = &executeProofCheck;
                    simplify = true;
                } else
                {
                    throw MultipleTargetsException(option);
                }
                break;
            case 'e':
                echo = true;
                break;
            case 'f':
                file.open(optarg);
                if (file.good())
                {
                    input = &file;
                } else
                {
                    throw InvalidFileException(optarg);
                }
                break;
            case 'i':
                try
                {
                    parser = inputSyntax.at(optarg);
                } catch (out_of_range & ex)
                {
                    throw IllegalValueException(option, optarg);
                }
                break;
            case 'l':
                try
                {
                    language = outputLanguage.at(optarg);
                } catch (out_of_range & ex)
                {
                    throw IllegalValueException(option, optarg);
                }
                break;
            case 'o':
                try
                {
                    printer = outputSyntax.at(optarg);
                } catch (out_of_range & ex)
                {
                    throw IllegalValueException(option, optarg);
                }
                break;
            case 'P':
                if (target == NULL)
                {
                    target = &executeProofCheck;
                } else
                {
                    throw MultipleTargetsException(option);
                }
                break;
            case 's':
                strict = true;
                break;
            case '?':
                throw IllegalOptionException(optopt);
                break;
            case ':':
                throw MissingValueException(optopt);
                break;
        }
    }
    if (target == NULL)
    {
        target = &executeDefault;
    }
}

Configuration::~Configuration()
{
    if (file.is_open())
    {
        file.close();
    }
}

Formula * Configuration::parse() const
{
    return parser(*input);
}

string Configuration::print(Formula * formula) const
{
    return (formula->*printer)(language);
}

Target Configuration::getTarget() const
{
    return target;
}

bool Configuration::getEcho() const
{
    return echo;
}

bool Configuration::getStrict() const
{
    return strict;
}

bool Configuration::getSimplify() const
{
    return simplify;
}
