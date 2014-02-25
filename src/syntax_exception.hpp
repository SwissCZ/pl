#ifndef SYNTAX_EXCEPTION_HPP
#define	SYNTAX_EXCEPTION_HPP

#include <exception>

using namespace std;

class SyntaxException : public exception
{
protected:
    const char * program_name;
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

class FileNotFoundException : public SyntaxException
{
private:
    char parameter;
public:
    FileNotFoundException(const char *, const char);
    virtual const char * what() const throw ();
};

#endif	/* SYNTAX_EXCEPTION_HPP */
