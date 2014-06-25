#include <stdlib.h>

#include "configuration.hpp"
#include "executionTarget.hpp"
#include "usageException.hpp"

using namespace std;

int main(int argc,
         char** argv)
{
    try
    {
        Configuration config(argc, argv);
        return config.getTarget()->execute(config);
    } catch (UsageException& exception)
    {
        cerr << exception.getMessage() << endl;
        return EXIT_FAILURE;
    }
}
