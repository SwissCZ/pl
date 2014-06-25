#ifndef SYNTAX_EXCEPTION_HPP
#define	SYNTAX_EXCEPTION_HPP

#include <string>

using namespace std;

//! Program syntax exception

/**
 * Exception caused by invalid program syntax.
 */
class UsageException
{
private:
    char option;
    ///< Erroneous option

    string message;
    ///< Exception details
public:
    UsageException(char,
                   string);

    /**
     * Composes a syntax error message.
     * @return Syntax error message
     */
    string getMessage() const;
};

//! Illegal option exeption

/**
 * Thrown when an illegal option is set.
 */
class IllegalOptionException: public UsageException
{
public:
    IllegalOptionException(char);
};

//! Illegal value exception

/**
 * Thrown when an illegal option value is set.
 */
class IllegalValueException: public UsageException
{
public:
    IllegalValueException(char,
                          string);
};

//! Invalid file exception

/**
 * Thrown when an invalid file is given.
 */
class InvalidFileException: public UsageException
{
public:
    InvalidFileException(char,
                         string);
};

//! Missing value exception

/**
 * Thrown when a mandatory option value is not set.
 */
class MissingValueException: public UsageException
{
public:
    MissingValueException(char);
};

//! Multiple targets exception

/**
 * Thrown when multiple targets are set to be performed.
 */
class MultipleTargetsException: public UsageException
{
public:
    MultipleTargetsException(char);
};

#endif
