#include "parseException.hpp"

#include <sstream>

using namespace std;

ParseException::ParseException(string message) : message(message)
{
}

string ParseException::composeMessage() const
{
    return string() + message;
}

string ParseException::what() const
{
    return composeMessage() + ".";
}

IncompleteFormulaException::IncompleteFormulaException()
: ParseException("This formula is incomplete")
{
}

UnexpectedEOFException::UnexpectedEOFException()
: ParseException("Unexpected end of stream")
{
}

LocalizedParseException::LocalizedParseException(string message, char character,
                                                 int position)
: ParseException(message), character(character), position(position)
{
}

string LocalizedParseException::composeMessage() const
{
    stringstream stream;
    stream << message << " '" << character << "' at position " << position;
    return stream.str();
}

UnexpectedElementException::UnexpectedElementException(char character,
                                                       int position)
: LocalizedParseException("Unexpected element", character, position)
{
}

UnnecessaryElementException::UnnecessaryElementException(char character,
                                                         int position)
: LocalizedParseException("Unnecessary element", character, position)
{
}

IllegalCharacterException::IllegalCharacterException(char character,
                                                     int position)
: LocalizedParseException("Illegal character", character, position)
{
}
