#ifndef PARSE_EXCEPTION_HPP
#define	PARSE_EXCEPTION_HPP

#include <string>

using namespace std;

//! Formula parse error.

/**
 * Error occured during formula parsing.
 */
class ParseException
{
protected:
    string reason; ///< Error reason.

    /**
     * Composes a partial error message.
     * @return Partial error message.
     */
    virtual string preMessage() const;
public:
    ParseException(string);
    /**
     * Composes an error message.
     * @return Parse error message.
     */
    virtual string getMessage() const;
};

//! Incomplete formula error.

/**
 * Formula was not finished.
 */
class IncompleteFormulaException : public ParseException
{
public:
    IncompleteFormulaException();
};

//! Unexpected end of stream error.

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
    virtual string preMessage() const;
public:
    DetailedParseException(string, char, int);
};

//! Unexpected element error.

/**
 * Parsed element was not expected.
 */
class UnexpectedElementException : public DetailedParseException
{
public:
    UnexpectedElementException(char, int);
};

//! Unnecessary element error.

/**
 * Parsed formula has been already finished.
 */
class UnnecessaryElementException : public DetailedParseException
{
public:
    UnnecessaryElementException(char, int);
};

//! Illegal character error.

/**
 * Illegal character was read.
 */
class IllegalCharacterException : public DetailedParseException
{
public:
    IllegalCharacterException(char, int);
};

#endif
