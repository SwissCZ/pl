#ifndef SYNTAX_EXCEPTION_HPP
#define	SYNTAX_EXCEPTION_HPP

#include <exception>

using namespace std;

/**
 * Program syntax error.
 */
class SyntaxException : public exception
{
protected:
    const char * program_name; ///< This program's name
    char parameter; ///< Parameter that caused the error
public:
    SyntaxException(const char *, const char);
};

/**
 * Unsupported value error. Unsupported parameter value error was set.
 */
class UnsupportedValueException : public SyntaxException
{
public:
    UnsupportedValueException(const char *, const char);
    virtual const char * what() const throw ();
};

/**
 * File not found error. Specified file was not found.
 */
class FileNotFoundException : public SyntaxException
{
public:
    FileNotFoundException(const char *, const char);
    virtual const char * what() const throw ();
};

#endif	/* SYNTAX_EXCEPTION_HPP */
