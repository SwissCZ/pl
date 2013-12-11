#ifndef TOKEN_HPP
#define	TOKEN_HPP

enum TokenType
{
    PREPOSITION, CONNECTIVE, BRACKET
};

struct Token
{
    TokenType type;
    char id;
};

#endif	/* TOKEN_HPP */

