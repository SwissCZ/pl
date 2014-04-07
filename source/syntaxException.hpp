#ifndef SYNTAX_EXCEPTION_HPP
#define	SYNTAX_EXCEPTION_HPP

#include <string>

using namespace std;

//! Program syntax error.

/**
 * Invalid program usage error.
 */
class SyntaxException
{
protected:
    char option; ///< Error option character.
    string message; ///< Error message component.
    /**
     * Composes a partial error message.
     * @return Partial error message.
     */
    virtual string composeMessage() const;
public:
    SyntaxException(char, string);
    /**
     * Composes an error message.
     * @return Syntax error message.
     */
    string getMessage() const;
};

//! Exclusive targets error.

/**
 * Exclusive targets were set to be performed.
 */
class ExclusiveTargetsException : public SyntaxException
{
public:
    ExclusiveTargetsException(char);
};

//! Illegal option error.

/**
 * Illegal option was used.
 */
class IllegalOptionException : public SyntaxException
{
public:
    IllegalOptionException(char);
};

//! Missing value error.

/**
 * Required option value was not set.
 */
class MissingValueException : public SyntaxException
{
public:
    MissingValueException(char);
};

//! Option value error.

/**
 * Syntax error caused by invalid option value.
 */
class ValueException : public SyntaxException
{
private:
    string const value; ///< Error causing option value.
    virtual string composeMessage() const;
public:
    ValueException(char, string, string);
};

//! Illegal option value.

/**
 * Illegal option value was used.
 */
class IllegalValueException : public ValueException
{
public:
    IllegalValueException(char, string);
};

//! File not found.

/**
 * Given file was not found.
 */
class InvalidFileException : public ValueException
{
public:
    InvalidFileException(string);
};

#endif	/* SYNTAX_EXCEPTION_HPP */
