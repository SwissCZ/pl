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
 * 
 * @param argc Command line arguments count
 * @param argv Command line arguments array
 * @return STATUS_OK on proper execution, STATUS_ERROR otherwise.
 */
int main(int argc, char ** argv)
{
    // Variables definition
    Settings * settings; //< Program settings structure
    int exit_code = STATUS_OK; //< Program exit status code

    // Command line arguments processing
    try
    {
        settings = new Settings(argc, argv);
    } catch (SyntaxException & ex)
    {
        cerr << ex.what() << endl;
        exit_code = STATUS_ERROR;
    }

    // Program execution
    if (exit_code == STATUS_OK)
    {
        switch (settings->target)
        {
            case DEFAULT:
                Formula * formula;
                do
                {
                    try
                    {
                        formula = parseInfix(*(settings->input_stream));
                        delete formula;
                    } catch (ParseException & ex)
                    {
                        cerr << ex.what() << endl;
                        exit_code = STATUS_ERROR;
                    }
                } while (formula != NULL && exit_code == STATUS_OK);
                break;
            default:
                cerr << "Unimplemented target." << endl;
                exit_code = STATUS_ERROR;
                break;
        }
    }

    // Cleanup & exit
    delete settings;

    return exit_code;
}
