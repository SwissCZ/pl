#ifndef PARSE_EXCEPTION_HPP
#define	PARSE_EXCEPTION_HPP

#include <exception>

using namespace std;

/**
 * Formula parse error. Indicates invalid formula syntax.
 */
class ParseException : public exception
{
};

/**
 * Localized error. Parse error specified by the character and position.
 */
class LocalizedParseException : public ParseException
{
protected:
    char character; ///< Character causing the error
    int position; ///< Error-causing character position
public:
    LocalizedParseException(const char &, const int &);
};

/**
 * Unexpected element. Parsed element was not expected at current position.
 */
class UnexpectedElementException : public LocalizedParseException
{
public:
    UnexpectedElementException(const char &, const int &);
    virtual const char * what() const throw ();
};

/**
 * Unnecessary element. The formula has been already finished before parsing
 * this element.
 */
class UnnecessaryElementException : public LocalizedParseException
{
public:
    UnnecessaryElementException(const char &, const int &);
    virtual const char * what() const throw ();
};

/**
 * Illegal character. Illegal character was read.
 */
class IllegalCharacterException : public LocalizedParseException
{
public:
    IllegalCharacterException(const char &, const int &);
    virtual const char * what() const throw ();
};

/**
 * Incomplete formula. The formula has not been finished yet.
 */
class IncompleteFormulaException : public ParseException
{
public:
    IncompleteFormulaException();
    virtual const char * what() const throw ();
};

/**
 * Unexpected end of stream. The stream end was not expected yet.
 */
class UnexpectedEOFException : public ParseException
{
public:
    UnexpectedEOFException();
    virtual const char * what() const throw ();
};

#endif	/* PARSE_EXCEPTION_HPP */
