#include <fstream>
#include <getopt.h>
#include <map>
#include <streambuf>

#include "configuration.hpp"
#include "syntax_exception.hpp"

Configuration::Configuration(int argc, char** argv)
{
    string temp;
    std::map<const char *, Language> languageMap = {
        {"ascii", ASCII},
        {"words", WORDS},
        {"tex", TEX}
    };

    while (getopt(argc, argv, "i:o:l:f:") != -1)
    {
        switch (optopt)
        {
            case 'i':
                temp = optarg;
                if (temp == "prefix")
                {
                    parse = &parsePrefix;
                } else if (temp == "infix")
                {
                    parse = &parseInfix;
                } else if (temp == "postfix")
                {
                    parse = &parsePostfix;
                } else
                {
                    throw UnsupportedValueException(argv[0], optopt);
                }
                break;
            case 'o':
                temp = optarg;
                if (temp == "prefix")
                {
                    print = &Formula::printPrefix;
                } else if (temp == "infix")
                {
                    print = &Formula::printInfix;
                } else if (temp == "postfix")
                {
                    print = &Formula::printPostfix;
                } else
                {
                    throw UnsupportedValueException(argv[0], optopt);
                }
                break;
            case 'l':
                try
                {
                    outputLanguage = languageMap.at(optarg);
                } catch (std::out_of_range & ex)
                {
                    if (!std::string(optarg).empty())
                    {
                        throw UnsupportedValueException(argv[0], optopt);
                    }
                }
                break;
            case 'f':
                inputStream = new std::ifstream(optarg, std::ios::binary
                        | std::ios::in);

                if (inputStream->fail() && !std::string(optarg).empty())
                {
                    throw FileNotFoundException(argv[0], optopt);
                }
                break;
        }
    }
}

Configuration::~Configuration()
{
    delete inputStream;
}

