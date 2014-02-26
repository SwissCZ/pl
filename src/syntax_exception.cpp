#include <string>

#include "syntax_exception.hpp"

SyntaxException::SyntaxException(const char * program, const char parameter)
{
    this->program_name = program;
    this->parameter = parameter;
}

UnsupportedValueException::UnsupportedValueException(const char * program, const char parameter) : SyntaxException(program, parameter)
{
}

const char * UnsupportedValueException::what() const throw ()
{
    return (std::string() + program_name + ": " + "invalid option value -- " + parameter).c_str();
}

FileNotFoundException::FileNotFoundException(const char * program, const char parameter) : SyntaxException(program, parameter)
{
}

const char * FileNotFoundException::what() const throw ()
{
    return (std::string() + program_name + ": " + "file not found -- " + parameter).c_str();
}
