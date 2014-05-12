#include <unistd.h>

#include "configuration.hpp"
#include "target.hpp"
#include "syntaxException.hpp"

using namespace std;

int main(int argc, char ** argv)
{
    int exit = 1;
    Configuration * configuration = NULL;

    opterr = 0;
    try
    {
        configuration = new Configuration(argc, argv);
        exit = configuration->getTarget()(configuration);
    } catch (SyntaxException & exception)
    {
        cerr << exception.getMessage() << endl;
    }

    delete configuration;
    return exit;
}
