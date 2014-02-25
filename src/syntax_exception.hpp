#ifndef SYNTAX_EXCEPTION_HPP
#define	SYNTAX_EXCEPTION_HPP

#include <exception>

class SyntaxException : public std::exception
{
protected:
    const char * program;
public:
    SyntaxException(const char *);
};

class UnsupportedValueException : public SyntaxException
{
private:
    char parameter;
public:
    UnsupportedValueException(const char *, const char);
    virtual const char * what() const throw ();
};

#endif	/* SYNTAX_EXCEPTION_HPP */

