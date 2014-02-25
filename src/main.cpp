#include "settings.hpp"
#include "syntax_exception.hpp"
#include "parse.hpp"

int main(int argc, char ** argv)
{
    // Variables definition
    Settings * settings; //< Program settings structure
    int exit_code = 0; //< Program exit status code

    // Command line arguments processing
    try
    {
        settings = new Settings(argc, argv);
    } catch (SyntaxException & ex)
    {
        std::cerr << ex.what() << std::endl;
        exit_code = 1;
    }

    // Input data parsing
    //
    // Todo...
    
    Formula * formula;
    while((formula = parseInfix(*(settings->input_stream))) != NULL){
        std::cout << formula->printInfix(settings->output_language);
    }

    // Program target execution
    //
    // Todo...

    // Cleanup & exit
    delete settings;

    return exit_code;
}
