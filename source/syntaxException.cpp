#include "syntaxException.hpp"

using namespace std;

SyntaxException::SyntaxException(char option, string message)
: option(option), message(message)
{
}

string SyntaxException::composeMessage() const
{
    return string() + "Option '-"  + option + "' " + message;
}

string SyntaxException::what() const
{
    return composeMessage() + ".";
}

MultipleTargetsException::MultipleTargetsException(char option)
: SyntaxException(option, "is redundant")
{
}

IllegalOptionException::IllegalOptionException(char option)
: SyntaxException(option, "is illegal")
{
}

MissingValueException::MissingValueException(char option)
: SyntaxException(option, "has no value")
{
}

ValueException::ValueException(char option, string value, string message)
: SyntaxException(option, message), value(value)
{
}

string ValueException::composeMessage() const
{
    return string() + SyntaxException::composeMessage() + " '" + value + "'";
}

IllegalValueException::IllegalValueException(char option, string value)
: ValueException(option, value, "can not take value of")
{
}

FileNotFoundException::FileNotFoundException(string value)
: ValueException('i', value, "can not take missing file")
{
}
