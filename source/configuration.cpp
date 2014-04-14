#include "configuration.hpp"
#include "parseException.hpp"
#include "syntaxException.hpp"
#include "target.hpp"

#include <fstream>
#include <unistd.h>

using namespace std;

map<string, Parser> Configuration::inputSyntax = {
    {"prefix", &parsePrefix},
    {"infix", &parseInfix},
    {"postfix", &parsePostfix}
};
map<string, Printer> Configuration::outputSyntax = {
    {"prefix", &Formula::printPrefix},
    {"infix", &Formula::printInfix},
    {"postfix", &Formula::printPostfix}
};
map<string, Language> Configuration::outputLanguage = {
    {"ascii", ASCII},
    {"words", WORDS},
    {"tex", TEX}
};

Configuration::Configuration(int argc, char ** argv)
{
    int option;

    while ((option = getopt(argc, argv, "ADef:i:l:o:Ps")) != -1)
    {
        switch (option)
        {
            case 'A':
                if (target == NULL)
                {
                    target = new AxiomCheck();
                } else
                {
                    throw ExclusiveTargetsException(option);
                }
                break;
            case 'D':
                if (target == NULL)
                {
                    target = new ProofSimplify();
                } else
                {
                    throw ExclusiveTargetsException(option);
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
                    target = new ProofCheck();
                } else
                {
                    throw ExclusiveTargetsException(option);
                }
                break;
            case 's':
                strict = true;
                break;
            default:
                if (optopt == 'f' || optopt == 'i' || optopt == 'l' ||
                    optopt == 'o')
                {
                    throw MissingValueException(optopt);
                } else
                {
                    throw IllegalOptionException(optopt);
                }
                break;
        }
    }
    if (target == NULL)
    {
        target = new DefaultTarget();
    }
}

Configuration::~Configuration()
{
    if (file.is_open()) file.close();
    delete target;
}

istream * Configuration::getInput() const
{
    return input;
}

Parser Configuration::getParser() const
{
    return parser;
}

Printer Configuration::getPrinter() const
{
    return printer;
}

Language Configuration::getLanguage() const
{
    return language;
}

Target * Configuration::getTarget() const
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
