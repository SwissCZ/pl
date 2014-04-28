#ifndef SYNTAX_EXCEPTION_HPP
#define	SYNTAX_EXCEPTION_HPP

#include <string>

using namespace std;

//! Program usage syntax error.

/**
 * Invalid program usage syntax.
 */
class SyntaxException
{
protected:
    char option; ///< Error option character.
    string reason; ///< Error reason.

    /**
     * Composes a partial error message.
     * @return Partial error message.
     */
    virtual string preMessage() const;
public:
    SyntaxException(char, string);
    /**
     * Composes an error message.
     * @return Syntax error message.
     */
    string getMessage() const;
};

//! Multiple exclusive targets error.

/**
 * Multiple exclusive targets were set to be performed.
 */
class ExclusiveTargetsException : public SyntaxException
{
public:
    ExclusiveTargetsException(char);
};

//! Illegal option error.

/**
 * Illegal option was set.
 */
class IllegalOptionException : public SyntaxException
{
public:
    IllegalOptionException(char);
};

//! Missing option value error.

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
    string value; ///< Error causing option value.

    virtual string preMessage() const;
public:
    ValueException(char, string, string);
};

//! Illegal option value error.

/**
 * Illegal option value was set.
 */
class IllegalValueException : public ValueException
{
public:
    IllegalValueException(char, string);
};

//! File not found error.

/**
 * Given file can not be openned.
 */
class InvalidFileException : public ValueException
{
public:
    InvalidFileException(string);
};

#endif
