/**
 * @mainpage Handle formulas of propositional logic
 *
 * <h1>About</h1>
 * 
 * Description here.
 */

#include "settings.hpp"
#include "syntax_exception.hpp"
#include "parse.hpp"
#include "parse_exception.hpp"

#define STATUS_OK 0
#define STATUS_ERROR 1

using namespace std;

/**
 * Main program function.
 * @param argc Command line arguments count
 * @param argv Command line arguments array
 * @return STATUS_OK on proper execution, STATUS_ERROR otherwise.
 */
int main(int argc, char ** argv)
{
    // Variables definition
    Configuration * configuration = NULL;
    int exitCode = STATUS_OK;

    // Command line arguments processing
    try
    {
        configuration = new Configuration(argc, argv);
    } catch (SyntaxException & ex)
    {
        cerr << ex.what() << endl;
        exitCode = STATUS_ERROR;
    }

    // Program execution
    if (exitCode == STATUS_OK)
    {
        switch (configuration->target)
        {
            case DEFAULT:
                Formula * formula;
                try
                {
                    while ((formula = parseInfix(*(configuration->inputStream))) != NULL)
                    {
                        delete formula;
                    }
                } catch (ParseException & ex)
                {
                    cerr << ex.what() << endl;
                    exitCode = STATUS_ERROR;
                }
                break;
            default:
                cerr << "Unimplemented target." << endl;
                exitCode = STATUS_ERROR;
                break;
        }
    }

    // Cleanup & exit
    delete configuration;

    return exitCode;
}
