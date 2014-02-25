#include <string>

#include "syntax_exception.hpp"

SyntaxException::SyntaxException(const char * program)
{
    this->program = program;
}

UnsupportedValueException::UnsupportedValueException(const char * program, const char parameter) : SyntaxException(program)
{
    this->parameter = parameter;
}

const char * UnsupportedValueException::what() const throw ()
{
    return (std::string() + program + ": " + "invalid option value -- " + parameter).c_str();
}

