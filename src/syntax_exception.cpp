#include <string>

#include "syntax_exception.hpp"

using namespace std;

SyntaxException::SyntaxException(const char * programName, const char * message, const char parameter)
{
    this->programName = programName;
    this->message = message;
    this->parameter = parameter;
}

const char * SyntaxException::what() const throw ()
{
    return (string() + programName + ": " + message + " -- " + parameter).c_str();
}

MultipleTargetsException::MultipleTargetsException(const char * program, const char parameter) : SyntaxException(program, "too many targets", parameter)
{
}

UnsupportedValueException::UnsupportedValueException(const char * program, const char parameter) : SyntaxException(program, "invalid option value", parameter)
{
}

FileNotFoundException::FileNotFoundException(const char * program, const char parameter) : SyntaxException(program, "file not found", parameter)
{
}
