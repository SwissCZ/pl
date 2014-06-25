#include "usageException.hpp"

UsageException::UsageException(char option,
                               string message)
: option(option), message(message)
{
}

string UsageException::getMessage() const
{
    return string() + "'-" + option + "': " + message + ".";
}

IllegalOptionException::IllegalOptionException(char option)
: UsageException(option,
                 "This is an illegal option")
{
}

IllegalValueException::IllegalValueException(char option,
                                             string value)
: UsageException(option,
                 "Given value '" + value + "' is invalid")
{
}

InvalidFileException::InvalidFileException(char option,
                                           string value)
: UsageException(option,
                 "Given file '" + value + "' is invalid")
{
}

MissingValueException::MissingValueException(char option)
: UsageException(option,
                 "No option value was given")
{
}

MultipleTargetsException::MultipleTargetsException(char option)
: UsageException(option,
                 "Multiple targets were set")
{
}
