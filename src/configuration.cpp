#include "configuration.hpp"
#include "parseException.hpp"
#include "syntaxException.hpp"

#include <fstream>
#include <unistd.h>

using namespace std;

map<string, parse> Configuration::INPUT_NOTATION = {
    {"prefix", &parsePrefix},
    {"infix", &parseInfix},
    {"postfix", &parsePostfix}
};
map<string, print> Configuration::OUTPUT_NOTATION = {
    {"prefix", &Formula::printPrefix},
    {"infix", &Formula::printInfix},
    {"postfix", &Formula::printPostfix}
};
map<string, Language> Configuration::OUTPUT_LANGUAGE = {
    {"ascii", ASCII},
    {"words", WORDS},
    {"tex", TEX}
};

Configuration::Configuration(int argc, char ** argv)
{
    while (getopt(argc, argv, "Aef:i:l:o:P") != -1)
    {
        switch (optopt)
        {
            case 'A':
                if (target == NULL)
                {
                    target = new AxiomChecker();
                } else
                {
                    throw MultipleTargetsException(optopt);
                }
                break;
            case 'e':
                echo = true;
                break;
            case 'f':
                inputStream = new ifstream(optarg, ios::in);
                if (inputStream->fail() || string(optarg).empty())
                {
                    throw FileNotFoundException(optarg);
                }
                break;
            case 'i':
                try
                {
                    parser = INPUT_NOTATION.at(optarg);
                } catch (out_of_range & ex)
                {
                    throw IllegalValueException(optopt, optarg);
                }
                break;
            case 'l':
                try
                {
                    language = OUTPUT_LANGUAGE.at(optarg);
                } catch (out_of_range & ex)
                {
                    throw IllegalValueException(optopt, optarg);
                }
                break;
            case 'o':
                try
                {
                    printer = OUTPUT_NOTATION.at(optarg);
                } catch (out_of_range & ex)
                {
                    throw IllegalValueException(optopt, optarg);
                }
                break;
            case 'P':
                if (target == NULL)
                {
                    target = new ProofChecker();
                } else
                {
                    throw MultipleTargetsException(optopt);
                }
                break;
            default:
                throw IllegalOptionException(optopt);
                break;
        }
    }

    if (target == NULL)
    {
        target = new Target();
    }
}

Configuration::~Configuration()
{
    //delete inputStream;
    delete target;
}

istream * Configuration::getInput() const
{
    return inputStream;
}

parse Configuration::getParser() const
{
    return parser;
}

print Configuration::getPrinter() const
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
