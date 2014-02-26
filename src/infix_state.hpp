#ifndef INFIX_STATE_HPP
#define	INFIX_STATE_HPP

/**
 * Infix-format-parsed formula state.
 */
enum InfixState
{
    BLANK, ///< New level was openned
    FIRST_OPERAND, ///< First operand was set
    BINARY, ///< Binary operator was set
    LAST_OPERAND, ///< Last operand was set
    UNARY ///< Unary operator was set
};

#endif	/* INFIX_STATE_HPP */
