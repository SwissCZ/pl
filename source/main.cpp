#include "configuration.hpp"
#include "target.hpp"
#include "syntaxException.hpp"

#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char ** argv)
{
    // Variables definition.
    int exit;
    Configuration * configuration = NULL;

    // Turn off getopt() error messages as we have our own.
    opterr = 0;
    try
    {
        // Options processing.
        configuration = new Configuration(argc, argv);

        // Target execution.
        exit = configuration->getTarget()->execute(configuration);
    } catch (SyntaxException & exception)
    {
        // Print syntax error message.
        cerr << exception.getMessage() << endl;
        exit = EXIT_FAILURE;
    }

    // Program exit.
    delete configuration;
    return exit;
}
