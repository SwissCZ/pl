#include "syntaxException.hpp"

SyntaxException::SyntaxException(char option,
                                 string message)
: option(option), message(message)
{
}

string SyntaxException::getMessage() const
{
    return string() + "'-" + option + "': " + message + ".";
}

MultipleTargetsException::MultipleTargetsException(char option)
: SyntaxException(option,
                  "Multiple targets were set")
{
}

IllegalOptionException::IllegalOptionException(char option)
: SyntaxException(option,
                  "This is an illegal option")
{
}

MissingValueException::MissingValueException(char option)
: SyntaxException(option,
                  "No option value was given")
{
}

IllegalValueException::IllegalValueException(char option,
                                             string value)
: SyntaxException(option,
                  "Given value '" + value + "' is invalid")
{
}

InvalidFileException::InvalidFileException(char option,
                                           string value)
: SyntaxException(option,
                  "Given file '" + value + "' is invalid")
{
}
