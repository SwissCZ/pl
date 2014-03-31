#ifndef PARSE_EXCEPTION_HPP
#define	PARSE_EXCEPTION_HPP

#include <string>

using namespace std;

//! Formula parse error

/**
 * Error reported by parsers.
 */
class ParseException
{
protected:
    string message; ///< Error message string

    /**
     * Composes a parse error message.
     * @return Parse error message
     */
    virtual string getErrorMessage() const;
public:
    ParseException(string);
    virtual string what() const;
};

//! Incomplete formula.

/**
 * Parsed formula has not been finished.
 */
class IncompleteFormulaException : public ParseException
{
public:
    IncompleteFormulaException();
};

//! Unexpected end of stream.

/**
 * The end of input stream was not expected.
 */
class UnexpectedEOFException : public ParseException
{
public:
    UnexpectedEOFException();
};

//! Localized error

/**
 * Parse error localized with error-causing character position.
 */
class LocalizedParseException : public ParseException
{
protected:
    char character; ///< Error-causing character
    int position; ///< Error-causing character position

    virtual string getErrorMessage() const;
public:
    LocalizedParseException(string, char, int);
};

//! Unexpected element

/**
 * Parsed element was not expected at current position.
 */
class UnexpectedElementException : public LocalizedParseException
{
public:
    UnexpectedElementException(char, int);
};

//! Unnecessary element.

/**
 * Parsed formula has been already finished before parsing this element.
 */
class UnnecessaryElementException : public LocalizedParseException
{
public:
    UnnecessaryElementException(char, int);
};

//! Illegal character.

/**
 * Illegal character was read.
 */
class IllegalCharacterException : public LocalizedParseException
{
public:
    IllegalCharacterException(char, int);
};

#endif	/* PARSE_EXCEPTION_HPP */
