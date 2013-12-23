#include <iostream>
#include <limits>
#include <stack>

#include "infix_state.hpp"
#include "parse.hpp"
#include "language.hpp"

Formula * parsePrefix(std::istream & input)
{
    std::stack<Operator *> stack;
    Formula * temp;
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
                    // Top operator operands were not all set yet
                    temp = new Proposition(buffer);
                    while (stack.size() && stack.top()->addOperandRightwards(temp) == 0)
                    {
                        // Top operator operands were all set
                        temp = stack.top();
                        stack.pop();
                    }
                } else
                {
                    if (position == 1 && input.peek() == '\n')
                    {
                        // Atomic input
                        input.ignore();
                        return new Proposition(buffer);
                    } else if (position == 1 && input.peek() != '\n')
                    {
                        // Illegal position
                        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw position + 1;
                    } else
                    {
                        // No more operands are needed
                        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw position;
                    }
                }
                break;
            case NEGATION_CHAR:
                if (stack.size())
                {
                    // Top operator operands were not all set yet
                    stack.push(new UnaryOperator(buffer));
                } else
                {
                    if (position == 1)
                    {
                        // Initial operator
                        stack.push(new UnaryOperator(buffer));
                    } else
                    {
                        // No more operands are needed
                        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw position;
                    }
                }
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                if (stack.size())
                {
                    // Top operator operands were not set yet
                    stack.push(new BinaryOperator(buffer));
                } else
                {
                    if (position == 1)
                    {
                        // Initial operator
                        stack.push(new BinaryOperator(buffer));
                    } else
                    {
                        // No more operands are needed
                        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw position;
                    }
                }
                break;
            case ' ':
            case '\t':
                // Whitespace skipping
                break;
            case '\n':
                if (position == 1)
                {
                    // Formula sequence ending
                    return NULL;
                } else
                {
                    // Formula ending
                    position--;
                    run = false;
                }
                break;
            case EOF:
                if (position == 1)
                {
                    // Formula sequence ending
                    return NULL;
                } else
                {
                    // Invalid position
                    throw position;
                }
                break;
            default:
                input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw position;
                break;
        }
        position++;
    }

    if (stack.empty())
    {
        // All operands were set
        return temp;
    } else
    {
        // Some operator operands were not set
        throw position;
    }
}

Formula * parseInfix(std::istream & input)
{
    std::stack<Formula *> stack;
    std::stack<Operator *> operatorStack;
    std::stack<int> stateStack;
    Formula * temp;
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
                    if (position == 1 && input.peek() == '\n')
                    {
                        // Atomic input
                        input.ignore();
                        return new Proposition(buffer);
                    } else if (position == 1 && input.peek() != '\n')
                    {
                        // Illegal position
                        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw position + 1;
                    } else
                    {
                        // Illegal position
                        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw position;
                    }
                } else if (stateStack.top() == BLANK || stateStack.top() == OPERATOR)
                {
                    // First or second operand
                    stateStack.top()++;
                    stack.push(new Proposition(buffer));
                } else
                {
                    // Illegal position
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                }
                break;
            case NEGATION_CHAR:
                if (stateStack.empty())
                {
                    // Invalid position
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                } else if (stateStack.top() == BLANK)
                {
                    // Before operand
                    stateStack.top() = OPERATOR;
                    operatorStack.push(new UnaryOperator(buffer));
                } else
                {
                    // Invalid position
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                }
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                if (stateStack.empty())
                {
                    // Invalid position
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                } else if (stateStack.top() == FIRST)
                {
                    // Between operands
                    stateStack.top() = OPERATOR;
                    operatorStack.push(new BinaryOperator(buffer));
                } else
                {
                    // Invalid position
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
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
                        // Invalid position
                        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw position;
                    }
                } else if (stateStack.top() == BLANK || stateStack.top() == OPERATOR)
                {
                    // Minor formula openning
                    stateStack.push(BLANK);
                } else
                {
                    // Invalid position
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                }
                break;
            case ')':
                if (stateStack.empty())
                {
                    // Too much closing brackets
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                } else if (stateStack.top() == SECOND)
                {
                    // Minor formula closing
                    stateStack.pop();
                    if (stateStack.size())
                    {
                        stateStack.top()++;
                    }
                    do
                    {
                        temp = stack.top();
                        stack.pop();
                    } while (operatorStack.top()->addOperandLeftwards(temp) > 0);
                    stack.push(operatorStack.top());
                    operatorStack.pop();
                } else
                {
                    // Invalid position
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                }
                break;
            case ' ':
            case '\t':
                // Whitespace skipping
                break;
            case '\n':
                if (position == 1)
                {
                    // Formula sequence ending
                    return NULL;
                } else
                {
                    // Formula ending
                    position--;
                    run = false;
                }
                break;
            case EOF:
                if (position == 1)
                {
                    // Formula sequence ending
                    return NULL;
                } else
                {
                    // Invalid position
                    throw position;
                }
                break;
            default:
                // Unrecognized character
                input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw position;
                break;
        }
        position++;
    }

    if (stateStack.empty())
    {
        // All brackets were closed
        return stack.top();
    } else
    {
        // Some brackets are still openned
        throw position;
    }
}

Formula * parsePostfix(std::istream & input)
{
    std::stack<Formula *> stack;
    Operator * temp;
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
            case NEGATION_CHAR:
                if (stack.size() >= 1)
                {
                    // Operand available
                    temp = new UnaryOperator(buffer);
                    temp->addOperandLeftwards(stack.top());
                    stack.pop();
                    stack.push(temp);
                } else
                {
                    // Not enough operands
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                }
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                if (stack.size() >= 2)
                {
                    // Pair of operands available
                    temp = new BinaryOperator(buffer);
                    for (int i = 0; i < 2; i++)
                    {
                        temp->addOperandLeftwards(stack.top());
                        stack.pop();
                    }
                    stack.push(temp);
                } else
                {
                    // Not enough operands
                    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw position;
                }
                break;
            case ' ':
            case '\t':
                // Whitespace skipping
                break;
            case '\n':
                if (position == 1)
                {
                    // Formula sequence ending
                    return NULL;
                } else
                {
                    // Formula ending
                    position--;
                    run = false;
                }
                break;
            case EOF:
                if (position == 1)
                {
                    // Formula sequence ending
                    return NULL;
                } else
                {
                    // Invalid EOF position
                    throw position;
                }
                break;
            default:
                // Unrecognized character
                input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw position;
                break;
        }
        position++;
    }

    if (stack.size() == 1)
    {
        // All operands were used
        return stack.top();
    } else
    {
        // Some operands were not used
        throw position;
    }
}
