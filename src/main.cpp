/**
 * @mainpage Propositional logic formulas handler
 *
 * <h2>About</h2>
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
                formula = NULL;
                do
                {
                    try
                    {
                        delete formula;
                        formula = parseInfix(*(configuration->inputStream));
                    } catch (ParseException & ex)
                    {
                        cerr << ex.what() << endl;
                        exitCode = STATUS_ERROR;
                    }
                } while (formula != NULL && exitCode == STATUS_OK);
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
