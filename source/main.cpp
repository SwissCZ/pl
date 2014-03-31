#include "configuration.hpp"
#include "syntaxException.hpp"
#include "target.hpp"

#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char ** argv)
{
    // Variables definition
    int exit = EXIT_SUCCESS;
    Configuration * configuration = NULL;

    // Turn off getopt() error messages as we have our own
    opterr = 0;
    try
    {
        // Options processing
        configuration = new Configuration(argc, argv);

        // Target execution
        exit = configuration->getTarget()->perform(configuration);
    } catch (SyntaxException & exception)
    {
        // Print syntax error message
        cerr << exception.what() << endl;
        exit = EXIT_FAILURE;
    }

    // Program exit
    delete configuration;
    return exit;
}
