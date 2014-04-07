#ifndef PARSE_EXCEPTION_HPP
#define	PARSE_EXCEPTION_HPP

#include <string>

using namespace std;

//! Formula parser error.

/**
 * Error reported by formula parser.
 */
class ParseException
{
protected:
    string message; ///< Error message component.
    /**
     * Composes a partial error message.
     * @return Partial error message.
     */
    virtual string composeMessage() const;
public:
    ParseException(string);
    /**
     * Composes an error message.
     * @return Parse error message.
     */
    virtual string getMessage() const;
};

//! Incomplete formula parsed.

/**
 * Formula was not finished.
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

//! Detailed parse error.

/**
 * Parse error specified with error causing character and it's position.
 */
class DetailedParseException : public ParseException
{
protected:
    char character; ///< Error causing character.
    int position; ///< Error causing character position.
    virtual string composeMessage() const;
public:
    DetailedParseException(string, char, int);
};

//! Unexpected element parsed.

/**
 * Parsed element was not expected at current position.
 */
class UnexpectedElementException : public DetailedParseException
{
public:
    UnexpectedElementException(char, int);
};

//! Unnecessary element parsed.

/**
 * Parsed formula has been already finished before parsing this element.
 */
class UnnecessaryElementException : public DetailedParseException
{
public:
    UnnecessaryElementException(char, int);
};

//! Illegal character read.

/**
 * Illegal character was read.
 */
class IllegalCharacterException : public DetailedParseException
{
public:
    IllegalCharacterException(char, int);
};

#endif	/* PARSE_EXCEPTION_HPP */
