#ifndef SYNTAX_EXCEPTION_HPP
#define	SYNTAX_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

//! Syntax error

/**
 * Invalid program usage syntax error.
 */
class SyntaxException : public exception
{
protected:
    char option; ///< Error option character
    string message; ///< Error message

    /**
     * Composes a syntax error message.
     * @return Syntax error message
     */
    virtual string getErrorMessage() const;
public:
    SyntaxException(char, string);
    virtual const char * what() const throw ();
};

//! Multiple targets error

/**
 * Multiple targets were set to be performed.
 */
class MultipleTargetsException : public SyntaxException
{
public:
    MultipleTargetsException(char);
};

//! Illegal option error

/**
 * Illegal option was used.
 */
class IllegalOptionException : public SyntaxException
{
public:
    IllegalOptionException(char);
};

//! Missing option value

/**
 * Required option value is missing.
 */
class MissingValueException : public SyntaxException
{
public:
    MissingValueException(char);
};

//! Illegal option value

/**
 * Syntax error caused by invalid option value.
 */
class ValueException : public SyntaxException
{
private:
    string const value; ///< Error-causing option value

    virtual string getErrorMessage() const;
public:
    ValueException(char, string, string);
};

//! Illegal option value

/**
 * Illegal option value was used.
 */
class IllegalValueException : public ValueException
{
public:
    IllegalValueException(char, string);
};

//! File not found

/**
 * Given file was not found.
 */
class FileNotFoundException : public ValueException
{
public:
    FileNotFoundException(string);
};

#endif	/* SYNTAX_EXCEPTION_HPP */
