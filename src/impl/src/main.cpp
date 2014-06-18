#include "configuration.hpp"
#include "executionTarget.hpp"
#include "syntaxException.hpp"

using namespace std;

int main(int argc,
         char** argv)
{
    try
    {
        Configuration configuration(argc, argv);
        return configuration.getTarget()->execute(configuration);
    } catch (SyntaxException& exception)
    {
        cerr << exception.getMessage() << endl;
        return 1;
    }
}
