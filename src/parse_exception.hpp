#ifndef PARSE_EXCEPTION_HPP
#define	PARSE_EXCEPTION_HPP

#include <exception>

using namespace std;

class ParseException : public exception
{
};

class UnexpectedElementException : public ParseException
{
protected:
    char character;
    int position;
public:
    UnexpectedElementException(const char &, const int &);
    virtual const char * what() const throw ();
};

class UnnecessaryElementException : public ParseException
{
protected:
    char character;
    int position;
public:
    UnnecessaryElementException(const char &, const int &);
    virtual const char * what() const throw ();
};

class IllegalCharacterException : public ParseException
{
protected:
    char character;
    int position;
public:
    IllegalCharacterException(const char &, const int &);
    virtual const char * what() const throw ();
};

class IncompleteFormulaException : public ParseException
{
public:
    IncompleteFormulaException();
    virtual const char * what() const throw ();
};

class UnexpectedEOFException : public ParseException
{
public:
    UnexpectedEOFException();
    virtual const char * what() const throw ();
};

#endif	/* PARSE_EXCEPTION_HPP */
