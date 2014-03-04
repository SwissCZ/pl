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
        // Program configuration
        configuration = new Configuration(argc, argv);

        // Program execution
        switch (configuration->target)
        {
            case DEFAULT:
                Formula * formula;
                try
                {
                    while ((formula = parseInfix(*(configuration->inputStream)))
                            != NULL)
                    {
                        delete formula;
                    }
                } catch (ParseException & ex)
                {
                    cerr << ex.what() << endl;
                    exitCode = STATUS_ERROR;
                }
                break;
        }

        // Cleanup
        delete configuration;
    } catch (SyntaxException & ex)
    {
        // Syntax error
        cerr << ex.what() << endl;
        exitCode = STATUS_ERROR;
    }

    // Exit
    return exitCode;
}
