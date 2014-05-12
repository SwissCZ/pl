#include <sstream>

#include "parseException.hpp"

using namespace std;

ParseException::ParseException(string message) : reason(message)
{
}

string ParseException::prepareMessage() const
{
    return reason;
}

string ParseException::getMessage() const
{
    return prepareMessage() + ".";
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

string DetailedParseException::prepareMessage() const
{
    stringstream stream;

    stream << reason << " '" << character << "' at position " << position;
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
