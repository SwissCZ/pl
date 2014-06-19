#include <sstream>

#include "parseException.hpp"

ParseException::ParseException(string message)
: message(message)
{
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
                                               unsigned position)
: ParseException(message), character(character), position(position)
{
}

string DetailedParseException::getMessage() const
{
    stringstream stream;

    stream << message << " '" << character << "' at position " << position << ".";
    return stream.str();
}

UnexpectedElementException::UnexpectedElementException(char character,
                                                       unsigned position)
: DetailedParseException("Unexpected element",
                         character,
                         position)
{
}

RedundantElementException::RedundantElementException(char character,
                                                     unsigned position)
: DetailedParseException("Unnecessary element",
                         character,
                         position)
{
}

IllegalCharacterException::IllegalCharacterException(char character,
                                                     unsigned position)
: DetailedParseException("Illegal character",
                         character,
                         position)
{
}
