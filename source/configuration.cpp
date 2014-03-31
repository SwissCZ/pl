#include "configuration.hpp"
#include "parseException.hpp"
#include "syntaxException.hpp"
#include "target.hpp"

#include <fstream>
#include <unistd.h>

using namespace std;

map<string, Parser> Configuration::inputNotation = {
    {"prefix", &parsePrefix},
    {"infix", &parseInfix},
    {"postfix", &parsePostfix}
};
map<string, Printer> Configuration::outputNotation = {
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
    while ((option = getopt(argc, argv, "Aef:i:l:o:P")) != -1)
    {
        switch (option)
        {
            case 'A':
                if (target == NULL)
                {
                    target = new AxiomChecker();
                } else
                {
                    throw MultipleTargetsException(option);
                }
                break;
            case 'e':
                echo = true;
                break;
            case 'f':
                fileStream.open(optarg);
                if (fileStream.fail() || string(optarg).empty())
                {
                    throw FileNotFoundException(optarg);
                } else {
                    inputStream = &fileStream;
                }
                break;
            case 'i':
                try
                {
                    parser = inputNotation.at(optarg);
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
                    printer = outputNotation.at(optarg);
                } catch (out_of_range & ex)
                {
                    throw IllegalValueException(option, optarg);
                }
                break;
            case 'P':
                if (target == NULL)
                {
                    target = new ProofChecker();
                } else
                {
                    throw MultipleTargetsException(option);
                }
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
        target = new Target();
    }
}

Configuration::~Configuration()
{
    fileStream.close();
    delete target;
}

istream * Configuration::getInput() const
{
    return inputStream;
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
