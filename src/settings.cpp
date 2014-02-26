#include <unistd.h>
#include <map>
#include <fstream>
#include <streambuf>

#include "settings.hpp"
#include "syntax_exception.hpp"

Configuration::Configuration(int argc, char** argv)
{
    std::map<std::string, Notation> notationMap = {
        {"prefix", PREFIX},
        {"infix", INFIX},
        {"postfix", POSTFIX}
    };
    std::map<const char *, Language> languageMap = {
        {"ascii", ASCII},
        {"common", COMMON},
        {"tex", TEX}
    };

    while (getopt(argc, argv, "i:o:l:f:") != -1)
    {
        switch (optopt)
        {
            case 'i':
                try
                {
                    inputNotation = notationMap.at(optarg);
                } catch (std::out_of_range & ex)
                {
                    if (!std::string(optarg).empty())
                    {
                        throw UnsupportedValueException(argv[0], optopt);
                    }
                }
                break;
            case 'o':
                try
                {
                    outputNotation = notationMap.at(optarg);
                } catch (std::out_of_range & ex)
                {
                    if (!std::string(optarg).empty())
                    {
                        throw UnsupportedValueException(argv[0], optopt);
                    }
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
                inputStream = new std::ifstream(optarg, std::ios::binary | std::ios::in);

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

