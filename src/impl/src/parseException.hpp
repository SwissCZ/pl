#ifndef PARSE_EXCEPTION_HPP
#define	PARSE_EXCEPTION_HPP

#include <string>

using namespace std;

//! Formula parse exception

/**
 * Exception caused by incorrect formula parsing.
 */
class ParseException
{
protected:
    string message;
    ///< Exception details
public:
    ParseException(string);

    /**
     * Composes an error message.
     * @return Parse error message
     */
    virtual string getMessage() const;
};

//! Detailed parse exception

/**
 * Exception specified with an error causing character and it's position.
 */
class DetailedParseException: public ParseException
{
protected:
    char character;
    ///< Erroneous character

    unsigned position;
    ///< Erroneous character position
public:
    DetailedParseException(string,
                           char,
                           unsigned);
    virtual string getMessage() const;
};

//! Incomplete formula exception

/**
 * Thrown when a formula is not finished.
 */
class IncompleteFormulaException: public ParseException
{
public:
    IncompleteFormulaException();
};

//! Unexpected end of stream exception

/**
 * Thrown when the end of the input stream is not expected.
 */
class UnexpectedEOFException: public ParseException
{
public:
    UnexpectedEOFException();
};

//! Illegal character exception

/**
 * Thrown when an illegal character is read.
 */
class IllegalCharacterException: public DetailedParseException
{
public:
    IllegalCharacterException(char,
                              unsigned);
};

//! Redundant element exception

/**
 * Thrown when a redundant element is parsed after formula completion.
 */
class RedundantElementException: public DetailedParseException
{
public:
    RedundantElementException(char,
                              unsigned);
};

//! Unexpected element exception

/**
 * Thrown when a parsed element is not expected at it's position.
 */
class UnexpectedElementException: public DetailedParseException
{
public:
    UnexpectedElementException(char,
                               unsigned);
};

#endif
