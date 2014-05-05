#include "syntaxException.hpp"

using namespace std;

SyntaxException::SyntaxException(char option, string message)
: option(option), reason(message)
{
}

string SyntaxException::prepareMessage() const
{
    return string() + "Option '-" + option + "' " + reason;
}

string SyntaxException::getMessage() const
{
    return prepareMessage() + ".";
}

MultipleTargetsException::MultipleTargetsException(char option)
: SyntaxException(option, "is irrelevant")
{
}

IllegalOptionException::IllegalOptionException(char option)
: SyntaxException(option, "is illegal")
{
}

MissingValueException::MissingValueException(char option)
: SyntaxException(option, "requires a value")
{
}

ValueException::ValueException(char option, string value, string message)
: SyntaxException(option, message), value(value)
{
}

string ValueException::prepareMessage() const
{
    return SyntaxException::prepareMessage() + " '" + value + "'";
}

IllegalValueException::IllegalValueException(char option, string value)
: ValueException(option, value, "value is illegal")
{
}

InvalidFileException::InvalidFileException(string value)
: ValueException('i', value, "file is illegal")
{
}
