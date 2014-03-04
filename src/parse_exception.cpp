#include <sstream>

#include "parse_exception.hpp"

LocalizedParseException::LocalizedParseException
(const char & character, const int & position)
{
    this->character = character;
    this->position = position;
}

UnexpectedElementException::UnexpectedElementException
(const char & character, const int & position)
: LocalizedParseException(character, position)
{
}

const char * UnexpectedElementException::what() const throw ()
{
    std::stringstream stream;
    stream << "Unexpected element '"
            << character
            << "' at position "
            << position
            << ".";
    return stream.str().c_str();
}

UnnecessaryElementException::UnnecessaryElementException
(const char & character, const int & position)
: LocalizedParseException(character, position)
{
}

const char * UnnecessaryElementException::what() const throw ()
{
    std::stringstream stream;
    stream << "Unnecessary element '"
            << character
            << "' at position "
            << position
            << ".";
    return stream.str().c_str();
}

IllegalCharacterException::IllegalCharacterException
(const char & character, const int & position)
: LocalizedParseException(character, position)
{
}

const char * IllegalCharacterException::what() const throw ()
{
    std::stringstream stream;
    stream << "Illegal character '"
            << character
            << "' at position "
            << position
            << ".";
    return stream.str().c_str();
}

IncompleteFormulaException::IncompleteFormulaException()
{
}

const char * IncompleteFormulaException::what() const throw ()
{
    std::stringstream stream;
    stream << "This formula is incomplete.";
    return stream.str().c_str();
}

UnexpectedEOFException::UnexpectedEOFException()
{
}

const char * UnexpectedEOFException::what() const throw ()
{
    std::stringstream stream;
    stream << "Unexpected end of stream.";
    return stream.str().c_str();
}

