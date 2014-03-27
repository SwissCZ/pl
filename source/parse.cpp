#include "parse.hpp"
#include "parseException.hpp"

#include <cstdio>
#include <limits>
#include <stack>

using namespace std;

//! Infix bracket state

/**
 * Infix bracket completion state. The order must be preserved!
 */
enum InfixState
{
    UNARY, ///< Unary operator set
    BLANK, ///< New bracket openned
    FIRST_OPERAND, ///< First operand set
    BINARY, ///< Binary operator set
    LAST_OPERAND ///< Last operand set
} ;

Formula * parsePrefix(istream & input)
{
    char buffer;
    int position = 1;
    bool run = true;

    stack<Operator *> operatorStack;
    Formula * temporaryFormula = NULL;

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
                if (operatorStack.size())
                {
                    // Set this as a stack operator's operand
                    temporaryFormula = new Proposition(buffer);
                    while (operatorStack.size()
                           && !operatorStack.top()->append(temporaryFormula))
                    {
                        // Stack operator's operands were all set
                        temporaryFormula = operatorStack.top();
                        operatorStack.pop();
                    }
                } else
                {
                    if (position == 1)
                    {
                        // Trivial formula
                        temporaryFormula = new Proposition(buffer);
                    } else
                    {
                        // No more operands are needed
                        input.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw UnnecessaryElementException(buffer, position);
                    }
                }
                break;
            case '-':
                if (operatorStack.size())
                {
                    // Push this to the operator stack
                    operatorStack.push(new UnaryOperator(buffer));
                } else
                {
                    if (position == 1)
                    {
                        // Initial operator
                        operatorStack.push(new UnaryOperator(buffer));
                    } else
                    {
                        // No more operands are needed
                        input.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw UnnecessaryElementException(buffer, position);
                    }
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (operatorStack.size())
                {
                    // Push this to the operator stack
                    operatorStack.push(new BinaryOperator(buffer));
                } else
                {
                    if (position == 1)
                    {
                        // Initial operator
                        operatorStack.push(new BinaryOperator(buffer));
                    } else
                    {
                        // No more operands are needed
                        input.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw UnnecessaryElementException(buffer, position);
                    }
                }
                break;
            case ' ':
            case '\t':
                // Legal whitespace skipping
                position--;
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
                    // Unexpected stream end
                    throw UnexpectedEOFException();
                }
            default:
                // Illegal character
                input.ignore(numeric_limits<streamsize>::max(), '\n');
                throw IllegalCharacterException(buffer, position);
                break;
        }
        position++;
    }

    if (operatorStack.empty())
    {
        // Formula is complete
        return temporaryFormula;
    } else
    {
        // Formula is incomplete
        throw IncompleteFormulaException();
    }
}

Formula * parseInfix(istream & input)
{
    char buffer;
    int position = 1;
    bool run = true;

    stack<Formula *> formulaStack;
    stack<Operator *> operatorStack;
    stack<int> stateStack;
    Formula * temporaryFormula;

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
                    if (position == 1)
                    {
                        // Trivial formula
                        formulaStack.push(new Proposition(buffer));
                    } else
                    {
                        // Unexpected element location
                        input.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw UnexpectedElementException(buffer, position);
                    }
                } else if (stateStack.top() == BLANK ||
                           stateStack.top() == BINARY)
                {
                    // The first or the last operand
                    formulaStack.push(new Proposition(buffer));
                    stateStack.top()++;
                } else if (stateStack.top() == UNARY)
                {
                    // Unary operator operand
                    temporaryFormula = new Proposition(buffer);

                    // Close recent unary operators
                    do
                    {
                        operatorStack.top()->append(temporaryFormula);
                        temporaryFormula = operatorStack.top();
                        operatorStack.pop();
                        stateStack.pop();
                    } while (stateStack.size() && stateStack.top() == UNARY);

                    formulaStack.push(temporaryFormula);
                    if (stateStack.size())
                    {
                        stateStack.top()++;
                    }
                } else
                {
                    // Unexpected element location
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case '-':
                if (stateStack.empty() && position != 1)
                {
                    // No more elements are needed
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw UnnecessaryElementException(buffer, position);
                } else if ((stateStack.empty() && position == 1)
                           || stateStack.top() == BLANK
                           || stateStack.top() == BINARY
                           || stateStack.top() == UNARY)
                {
                    // Unary operation
                    stateStack.push(UNARY);
                    operatorStack.push(new UnaryOperator(buffer));
                } else
                {
                    // Unexpected element location
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (stateStack.empty())
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (position == 1)
                    {
                        // Unexpected element location
                        throw UnexpectedElementException(buffer, position);
                    } else
                    {
                        // No more elements are needed
                        throw UnnecessaryElementException(buffer, position);
                    }
                } else if (stateStack.top() == FIRST_OPERAND)
                {
                    // Between operands
                    stateStack.top() = BINARY;
                    operatorStack.push(new BinaryOperator(buffer));
                } else
                {
                    // Unexpected element location
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
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
                        // No more elements are needed
                        input.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw UnnecessaryElementException(buffer, position);
                    }
                } else if (stateStack.top() == BLANK
                           || stateStack.top() == BINARY
                           || stateStack.top() == UNARY)
                {
                    // Tree level openning
                    stateStack.push(BLANK);
                } else
                {
                    // Unexpected element location
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case ')':
                if (stateStack.empty())
                {
                    // Too much closing brackets
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw UnnecessaryElementException(buffer, position);
                } else if (stateStack.top() == LAST_OPERAND)
                {
                    // Tree level closing
                    stateStack.pop();
                    do
                    {
                        temporaryFormula = formulaStack.top();
                        formulaStack.pop();
                    } while (operatorStack.top()->insert(temporaryFormula) > 0);
                    formulaStack.push(operatorStack.top());
                    operatorStack.pop();

                    // Close recent unary operators
                    while (stateStack.size() && stateStack.top() == UNARY)
                    {
                        operatorStack.top()->append(formulaStack.top());
                        formulaStack.pop();
                        formulaStack.push(operatorStack.top());
                        operatorStack.pop();
                        stateStack.pop();
                    }

                    if (stateStack.size())
                    {
                        stateStack.top()++;
                    }
                } else
                {
                    // Unexpected element location
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case ' ':
            case '\t':
                // Legal whitespace skipping
                position--;
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
                    // Unexpected stream end
                    throw UnexpectedEOFException();
                }
                break;
            default:
                // Illegal character
                input.ignore(numeric_limits<streamsize>::max(), '\n');
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
            // Formula is complete
            return formulaStack.top();
        }
    } else
    {
        // Formula is incomplete
        throw IncompleteFormulaException();
    }
}

Formula * parsePostfix(istream & input)
{
    char buffer;
    int position = 1;
    bool run = true;

    stack<Formula *> formulaStack;
    Operator * temporaryOperator;

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
                formulaStack.push(new Proposition(buffer));
                break;
            case '-':
                if (formulaStack.size() > 0)
                {
                    // Stack operand available
                    temporaryOperator = new UnaryOperator(buffer);
                    temporaryOperator->insert(formulaStack.top());
                    formulaStack.pop();
                    formulaStack.push(temporaryOperator);
                } else
                {
                    // Not enough stack operands
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw UnnecessaryElementException(buffer, position);
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (formulaStack.size() > 1)
                {
                    // Two stack operands available
                    temporaryOperator = new BinaryOperator(buffer);
                    temporaryOperator->insert(formulaStack.top());
                    formulaStack.pop();
                    temporaryOperator->insert(formulaStack.top());
                    formulaStack.pop();
                    formulaStack.push(temporaryOperator);
                } else
                {
                    // Not enough stack operands
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw UnnecessaryElementException(buffer, position);
                }
                break;
            case ' ':
            case '\t':
                // Legal whitespace skipping
                position--;
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
                    // Unexpected stream end
                    throw UnexpectedEOFException();
                }
                break;
            default:
                // Illegal character
                input.ignore(numeric_limits<streamsize>::max(), '\n');
                throw IllegalCharacterException(buffer, position);
                break;
        }
        position++;
    }

    if (position == 2)
    {
        // Empty line was parsed
        return NULL;
    } else if (formulaStack.size() == 1)
    {
        // Formula is complete
        return temporaryOperator;
    } else
    {
        // Formula is incomplete
        throw IncompleteFormulaException();
    }
}
