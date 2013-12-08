#include <iostream>

#include "formula.hpp"
#include "notation.hpp"
#include "parser.hpp"

using namespace std;

int main(int argc, char** argv)
{
    std::string input;
    Parser parser;

    getline(cin, input);

    cout << (char)CONJUNCTION << endl;
    cout << parser.parse(input, PREFIX)->print(PREFIX);

    return 0;
}

