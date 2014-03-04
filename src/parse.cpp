#include <iostream>
#include <limits>
#include <stack>

#include "parse.hpp"
#include "parse_exception.hpp"

/**
 * Infix parser state. Infix parser bracket content state.
 */
enum InfixState
{
    BLANK, ///< New level was openned
    FIRST_OPERAND, ///< First operand was set
    BINARY, ///< Binary operator was set
    LAST_OPERAND, ///< Last operand was set
    UNARY ///< Unary operator was set
};

Formula * parsePrefix(std::istream & input)
{
    std::stack<Operator *> stack;
    Formula * tmp = NULL;
    char buffer;
    int position = 1;
    bool run = true;

    while (run)
    {
        switch (buffer = input.get())
        {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                if (stack.size())
                {
                    // Stack top operands are not all set
                    tmp = new Proposition(buffer);
                    while (stack.size() && stack.top()->appendFirst(tmp) == 0)
                    {
                        // Stack top operands are all set
                        tmp = stack.top();
                        stack.pop();
                    }
                } else
                {
                    if (position == 1)
                    {
                        // Trivial formula candidate
                        tmp = new Proposition(buffer);
                    } else
                    {
                        // No more operands are needed
                        input.ignore(std::numeric_limits<std::streamsize>::max()
                                , '\n');
                        throw UnnecessaryElementException(buffer, position);
                    }
                }
                break;
            case '-':
                if (stack.size())
                {
                    // Stack top operands are not all set
                    stack.push(new UnaryOperator(NEGATION));
                } else
                {
                    if (position == 1)
                    {
                        // Initial operator
                        stack.push(new UnaryOperator(NEGATION));
                    } else
                    {
                        // No more operands are needed
                        input.ignore(std::numeric_limits<std::streamsize>::max()
                                , '\n');
                        throw UnnecessaryElementException(buffer, position);
                    }
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (stack.size())
                {
                    // Stack top operands are not all set
                    stack.push(new BinaryOperator(connectiveMap.at(buffer)));
                } else
                {
                    if (position == 1)
                    {
                        // Initial operator
                        stack.push(new BinaryOperator(connectiveMap
                                .at(buffer)));
                    } else
                    {
                        // No more operands are needed
                        input.ignore(std::numeric_limits<std::streamsize>::max()
                                , '\n');
                        throw UnnecessaryElementException(buffer, position);
                    }
                }
                break;
            case ' ':
            case '\t':
                // Legal whitespace skipping
                break;
            case '\n':
                // Formula end
                run = false;
                break;
            case EOF:
                if (position == 1)
                {
                    // Formula sequence end
                    run = false;
                } else
                {
                    // Unexpected end of stream
                    run = false;
                    throw UnexpectedEOFException();
                }
            default:
                // Unrecognized character
                input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw IllegalCharacterException(buffer, position);
                break;
        }
        position++;
    }

    if (stack.empty())
    {
        // All operands were set
        return tmp;
    } else
    {
        // Some operands were not set
        throw IncompleteFormulaException();
    }
}

Formula * parseInfix(std::istream & input)
{
    std::stack<Formula *> stack;
    std::stack<Operator *> operatorStack;
    std::stack<int> stateStack;
    Formula * tmp;
    char buffer;
    int position = 1;
    bool run = true;

    while (run)
    {
        switch (buffer = input.get())
        {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                if (stateStack.empty())
                {
                    // First character case
                    if (position == 1)
                    {
                        // Trivial formula candidate
                        stack.push(new Proposition(buffer));
                    } else
                    {
                        // Illegal element position
                        input.ignore(std::numeric_limits<std::streamsize>::max()
                                , '\n');
                        throw UnexpectedElementException(buffer, position);
                    }
                } else if (stateStack.top() == BLANK ||
                        stateStack.top() == BINARY)
                {
                    // Before first or second operand
                    stateStack.top()++;
                    stack.push(new Proposition(buffer));
                } else if (stateStack.top() == UNARY)
                {
                    tmp = new Proposition(buffer);
                    do
                    {
                        operatorStack.top()->appendFirst(tmp);
                        tmp = operatorStack.top();
                        operatorStack.pop();
                        stateStack.pop();
                    } while (stateStack.size() && stateStack.top() == UNARY);
                    stack.push(tmp);
                    if (stateStack.size())
                    {
                        stateStack.top()++;
                    }
                } else
                {
                    // Illegal element position
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case '-':
                if (stateStack.empty() || stateStack.top() == BLANK
                        || stateStack.top() == BINARY
                        || stateStack.top() == UNARY)
                {
                    // Unary operation
                    stateStack.push(UNARY);
                    operatorStack.push(new UnaryOperator(NEGATION));
                } else
                {
                    // Illegal element position
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (stateStack.empty())
                {
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    if (position == 1)
                    {
                        // First character case
                        throw UnexpectedElementException(buffer, position);
                    } else
                    {
                        // Finished formula case
                        throw UnnecessaryElementException(buffer, position);
                    }
                } else if (stateStack.top() == FIRST_OPERAND)
                {
                    // Between operands
                    stateStack.top() = BINARY;
                    operatorStack.push(new BinaryOperator(
                            connectiveMap.at(buffer)));
                } else
                {
                    // Illegal element position
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case '(':
                if (stateStack.empty())
                {
                    if (position == 1)
                    {
                        // Initial openning bracket
                        stateStack.push(BLANK);
                    } else
                    {
                        // Illegal position
                        input.ignore(std::numeric_limits<std::streamsize>::max()
                                , '\n');
                        throw UnnecessaryElementException(buffer, position);
                    }
                } else if (stateStack.top() == BLANK
                        || stateStack.top() == BINARY
                        || stateStack.top() == UNARY)
                {
                    // Subformula openning
                    stateStack.push(BLANK);
                } else
                {
                    // Illegal position
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case ')':
                if (stateStack.empty())
                {
                    // Too much closing brackets
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    throw UnnecessaryElementException(buffer, position);
                } else if (stateStack.top() == LAST_OPERAND)
                {
                    // Subformula closing
                    stateStack.pop();
                    do
                    {
                        tmp = stack.top();
                        stack.pop();
                    } while (operatorStack.top()->appendLast(tmp) > 0);
                    stack.push(operatorStack.top());
                    operatorStack.pop();

                    while (stateStack.size() && stateStack.top() == UNARY)
                    {
                        operatorStack.top()->appendFirst(stack.top());
                        stack.pop();
                        stack.push(operatorStack.top());
                        operatorStack.pop();
                        stateStack.pop();
                    }
                    if (stateStack.size())
                    {
                        stateStack.top()++;
                    }
                } else
                {
                    // Illegal position
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case ' ':
            case '\t':
                // Legal whitespace skipping
                break;
            case '\n':
                // Formula ending
                run = false;
                break;
            case EOF:
                if (position == 1)
                {
                    // Formula sequence ending
                    run = false;
                } else
                {
                    // Unexpected end of stream
                    throw UnexpectedEOFException();
                }
                break;
            default:
                // Unrecognized character
                input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw IllegalCharacterException(buffer, position);
                break;
        }
        position++;
    }

    if (stateStack.empty())
    {
        if (position == 2)
        {
            // Empty line was parsed
            return NULL;
        } else
        {
            // All brackets were closed
            return stack.top();
        }
    } else
    {
        // Some brackets were not closed
        throw IncompleteFormulaException();
    }
}

Formula * parsePostfix(std::istream & input)
{
    std::stack<Formula *> stack;
    Operator * tmp;
    char buffer;
    int position = 1;
    bool run = true;

    while (run)
    {
        switch (buffer = input.get())
        {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                stack.push(new Proposition(buffer));
                break;
            case '-':
                if (stack.size() >= 1)
                {
                    // Operand available on the stack
                    tmp = new UnaryOperator(NEGATION);
                    tmp->appendLast(stack.top());
                    stack.pop();
                    stack.push(tmp);
                } else
                {
                    // Not enough operands on the stack
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    throw UnnecessaryElementException(buffer, position);
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (stack.size() >= 2)
                {
                    // Two operands available on the stack
                    tmp = new BinaryOperator(connectiveMap.at(buffer));
                    for (int i = 0; i < 2; i++)
                    {
                        tmp->appendLast(stack.top());
                        stack.pop();
                    }
                    stack.push(tmp);
                } else
                {
                    // Not enough operands on the stack
                    input.ignore(std::numeric_limits<std::streamsize>::max()
                            , '\n');
                    throw UnnecessaryElementException(buffer, position);
                }
                break;
            case ' ':
            case '\t':
                // Legal whitespace skipping
                break;
            case '\n':
                // Formula end
                run = false;
                break;
            case EOF:
                if (position == 1)
                {
                    // Formula sequence end
                    run = false;
                } else
                {
                    // Unexpected end of stream
                    throw UnexpectedEOFException();
                }
                break;
            default:
                // Unrecognized character
                input.ignore(std::numeric_limits<std::streamsize>::max()
                        , '\n');
                throw IllegalCharacterException(buffer, position);
                break;
        }
        position++;
    }

    if (position == 2)
    {
        // Empty line was parsed
        return NULL;
    } else
        if (stack.size() == 1)
    {
        // All operands were set
        return stack.top();
    } else
    {
        // Some operands were not set
        throw IncompleteFormulaException();
    }
}
