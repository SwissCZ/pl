#include <stdexcept>
#include <unistd.h>

#include "configuration.hpp"
#include "executionTarget.hpp"
#include "syntaxException.hpp"

map<string, Parser> Configuration::inputSyntaxes = {
    {"prefix", &parsePrefix},
    {"infix", &parseInfix},
    {"postfix", &parsePostfix}
};

map<string, Printer> Configuration::outputSyntaxes = {
    {"prefix", &Formula::printPrefix},
    {"infix", &Formula::printInfix},
    {"postfix", &Formula::printPostfix}
};

map<string, Language> Configuration::outputLanguages = {
    {"ascii", ASCII},
    {"words", WORDS},
    {"tex", TEX}
};

Configuration::Configuration(int argc,
                             char** argv)
{
    int option;

    opterr = 0;
    while ((option = getopt(argc, argv, ":Aef:i:l:O:o:P:s")) != -1)
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
                file.open(optarg);
                if (file.good())
                {
                    input = &file;
                } else
                {
                    throw InvalidFileException(option, optarg);
                }
                break;
            case 'i':
                try
                {
                    parser = inputSyntaxes.at(optarg);
                } catch (out_of_range& exception)
                {
                    throw IllegalValueException(option, optarg);
                }
                break;
            case 'l':
                try
                {
                    language = outputLanguages.at(optarg);
                } catch (out_of_range& exception)
                {
                    throw IllegalValueException(option, optarg);
                }
                break;
            case 'O':
                if (target == NULL)
                {
                    try
                    {
                        target = new ProofHandler(stoul(optarg), true);
                    } catch (invalid_argument& exception)
                    {
                        throw IllegalValueException(option, optarg);
                    } catch (out_of_range& exception)
                    {
                        throw IllegalValueException(option, optarg);
                    }
                } else
                {
                    throw MultipleTargetsException(option);
                }
                break;
            case 'o':
                try
                {
                    printer = outputSyntaxes.at(optarg);
                } catch (out_of_range& exception)
                {
                    throw IllegalValueException(option, optarg);
                }
                break;
            case 'P':
                if (target == NULL)
                {
                    try
                    {
                        target = new ProofHandler(stoul(optarg), false);
                    } catch (invalid_argument& exception)
                    {
                        throw IllegalValueException(option, optarg);
                    } catch (out_of_range& exception)
                    {
                        throw IllegalValueException(option, optarg);
                    }
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
        target = new DefaultTarget();
    }
    if (system == NULL)
    {
        system = new HilbertSystem();
    }
}

Configuration::~Configuration()
{
    if (file.is_open())
    {
        file.close();
    }
    delete target;
    delete system;
}

ExecutionTarget* Configuration::getTarget() const
{
    return target;
}

ProofSystem* Configuration::getSystem() const
{
    return system;
}

bool Configuration::getEcho() const
{
    return echo;
}

bool Configuration::getStrict() const
{
    return strict;
}

Formula* Configuration::parseFormula() const
{
    return parser(*input);
}

string Configuration::printFormula(Formula* formula) const
{
    return (formula->*printer)(language);
}
