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

string ParseException::getMessage() const
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

DetailedParseException::DetailedParseException(string message, char character,
                                                 int position)
: ParseException(message), character(character), position(position)
{
}

string DetailedParseException::composeMessage() const
{
    stringstream stream;
    stream << message << " '" << character << "' at position " << position;
    return stream.str();
}

UnexpectedElementException::UnexpectedElementException(char character,
                                                       int position)
: DetailedParseException("Unexpected element", character, position)
{
}

UnnecessaryElementException::UnnecessaryElementException(char character,
                                                         int position)
: DetailedParseException("Unnecessary element", character, position)
{
}

IllegalCharacterException::IllegalCharacterException(char character,
                                                     int position)
: DetailedParseException("Illegal character", character, position)
{
}
