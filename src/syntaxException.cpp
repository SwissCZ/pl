#include "syntaxException.hpp"

using namespace std;

SyntaxException::SyntaxException(char option, string message)
: option(option), message(message)
{
}

string SyntaxException::getErrorMessage() const
{
    return string() + "Option '-"  + option + "' " + message;
}

const char * SyntaxException::what() const throw ()
{
    return (getErrorMessage() + ".").c_str();
}

MultipleTargetsException::MultipleTargetsException(char option)
: SyntaxException(option, "is redundant")
{
}

IllegalOptionException::IllegalOptionException(char option)
: SyntaxException(option, "is illegal")
{
}

ValueException::ValueException(char option, string value, string message)
: SyntaxException(option, message), value(value)
{
}

string ValueException::getErrorMessage() const
{
    return string() + SyntaxException::getErrorMessage() + " '" + value + "'";
}

IllegalValueException::IllegalValueException(char option, string value)
: ValueException(option, value, "can not take value of")
{
}

FileNotFoundException::FileNotFoundException(string value)
: ValueException('i', value, "can not take missing file")
{
}
