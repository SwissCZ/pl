#ifndef PARSE_EXCEPTION_HPP
#define	PARSE_EXCEPTION_HPP

#include <exception>

class UnexpectedElementException : public std::exception
{
protected:
    char character;
    int position;
public:
    UnexpectedElementException(const char &, const int &);
    virtual const char * what() const throw ();
};

class UnnecessaryElementException : public std::exception
{
protected:
    char character;
    int position;
public:
    UnnecessaryElementException(const char &, const int &);
    virtual const char * what() const throw ();
};

class IllegalCharacterException : public std::exception
{
protected:
    char character;
    int position;
public:
    IllegalCharacterException(const char &, const int &);
    virtual const char * what() const throw ();
};

class IncompleteFormulaException : public std::exception
{
public:
    IncompleteFormulaException();
    virtual const char * what() const throw ();
};

class UnexpectedEOFException : public std::exception
{
public:
    UnexpectedEOFException();
    virtual const char * what() const throw ();
};

#endif	/* PARSE_EXCEPTION_HPP */

