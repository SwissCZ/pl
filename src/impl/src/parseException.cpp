#include <sstream>

#include "parseException.hpp"

ParseException::ParseException(string message)
{
    this->message = message;
}

string ParseException::getMessage() const
{
    return message + ".";
}

IncompleteFormulaException::IncompleteFormulaException()
: ParseException("Incomplete formula")
{
}

UnexpectedEOFException::UnexpectedEOFException()
: ParseException("Unexpected end of stream")
{
}

DetailedParseException::DetailedParseException(string message,
                                               char character,
                                               int position)
: ParseException(message)
{
    this->character = character;
    this->position = position;
}

string DetailedParseException::getMessage() const
{
    stringstream stream;

    stream << message << " '" << character << "' at position " << position << ".";
    return stream.str();
}

UnexpectedElementException::UnexpectedElementException(char character,
                                                       int position)
: DetailedParseException("Unexpected element",
                         character,
                         position)
{
}

RedundantElementException::RedundantElementException(char character,
                                                     int position)
: DetailedParseException("Unnecessary element",
                         character,
                         position)
{
}

IllegalCharacterException::IllegalCharacterException(char character,
                                                     int position)
: DetailedParseException("Illegal character",
                         character,
                         position)
{
}
