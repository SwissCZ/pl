#include <unistd.h>
#include <map>
#include <fstream>
#include <streambuf>

#include "settings.hpp"
#include "syntax_exception.hpp"

Settings::Settings(int argc, char** argv)
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
                    input_notation = notationMap.at(optarg);
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
                    output_notation = notationMap.at(optarg);
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
                    output_language = languageMap.at(optarg);
                } catch (std::out_of_range & ex)
                {
                    if (!std::string(optarg).empty())
                    {
                        throw UnsupportedValueException(argv[0], optopt);
                    }
                }
                break;
            case 'f':
                input_stream = new std::ifstream(optarg, std::ios::binary | std::ios::in);

                if (input_stream->fail() && !std::string(optarg).empty())
                {
                    std::cout << "asdf";
                }
                break;
        }
    }
}

Settings::~Settings()
{
    delete input_stream;
}

