#include "programConfiguration.hpp"
#include "parseException.hpp"
#include "syntaxException.hpp"
#include "executionTarget.hpp"

#include <fstream>
#include <unistd.h>

using namespace std;

map<string, Parser> ProgramConfiguration::inputNotation = {
    {"prefix", &parsePrefix},
    {"infix", &parseInfix},
    {"postfix", &parsePostfix}
};
map<string, Printer> ProgramConfiguration::outputNotation = {
    {"prefix", &PropositionalFormula::printPrefix},
    {"infix", &PropositionalFormula::printInfix},
    {"postfix", &PropositionalFormula::printPostfix}
};
map<string, Language> ProgramConfiguration::outputLanguage = {
    {"ascii", ASCII},
    {"words", WORDS},
    {"tex", TEX}
};

ProgramConfiguration::ProgramConfiguration(int argc, char ** argv)
{
    int option;
    while ((option = getopt(argc, argv, "Aef:i:l:o:P")) != -1)
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
            case 'e':
                echo = true;
                break;
            case 'f':
                fileStream.open(optarg);
                if (fileStream.fail())
                {
                    throw InvalidFileException(optarg);
                } else
                {
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
                    target = new ProofCheck();
                } else
                {
                    throw ExclusiveTargetsException(option);
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
        target = new DefaultTarget();
    }
}

ProgramConfiguration::~ProgramConfiguration()
{
    fileStream.close();
    delete target;
}

istream * ProgramConfiguration::getInput() const
{
    return inputStream;
}

Parser ProgramConfiguration::getParser() const
{
    return parser;
}

Printer ProgramConfiguration::getPrinter() const
{
    return printer;
}

Language ProgramConfiguration::getLanguage() const
{
    return language;
}

ExecutionTarget * ProgramConfiguration::getTarget() const
{
    return target;
}

bool ProgramConfiguration::getEcho() const
{
    return echo;
}
