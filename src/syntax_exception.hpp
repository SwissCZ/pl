#ifndef SYNTAX_EXCEPTION_HPP
#define	SYNTAX_EXCEPTION_HPP

#include <exception>

using namespace std;

/**
 * Syntax error. Used to signalize an invalid syntax on program usage.
 */
class SyntaxException : public exception
{
protected:
    const char * programName; ///< Program name
    const char * message; ///< Error message
    char parameter; ///< Parameter causing the error
public:
    SyntaxException(const char *, const char *, const char);
    virtual const char * what() const throw ();
};

/**
 * Multiple targets error. Multiple targets were set to be performed.
 */
class MultipleTargetsException : public SyntaxException
{
public:
    MultipleTargetsException(const char *, const char);
};

/**
 * Unsupported value error. Unsupported parameter value was set.
 */
class UnsupportedValueException : public SyntaxException
{
public:
    UnsupportedValueException(const char *, const char);
};

/**
 * File not found error. Specified file was not found.
 */
class FileNotFoundException : public SyntaxException
{
public:
    FileNotFoundException(const char *, const char);
};

#endif	/* SYNTAX_EXCEPTION_HPP */
