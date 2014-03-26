#include "configuration.hpp"
#include "syntaxException.hpp"

#include <exception>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char ** argv)
{
    // Variables definition
    int exit = EXIT_SUCCESS;
    Configuration * configuration = NULL;
    Formula * formula = NULL;

    opterr = 0; // Turn off getopt() error messages as we have our own
    try
    {
        // Options processing
        configuration = new Configuration(argc, argv);

        // Program execution
        do
        {
            // Formula parsing
            formula = configuration->getParser()(*(configuration->getInput()));
            if (formula == NULL) break;

            // Formula printing
            if (configuration->getEcho())
            {
                cout << (formula->*configuration->getPrinter())
                        (configuration->getLanguage()) << endl;
            }

            // Formula processing
        } while (configuration->getTarget()->next(formula));
    } catch (exception & ex)
    {
        // Syntax or parse error
        cerr << ex.what() << endl;
        exit = EXIT_FAILURE;
    }

    // Proper exit
    delete configuration;
    return exit;
}
