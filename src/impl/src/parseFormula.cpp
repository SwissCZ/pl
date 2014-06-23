#include <cstdio>
#include <limits>
#include <sstream>
#include <stack>

#include "parseException.hpp"
#include "parseFormula.hpp"

//! Bracket state

/**
 * Bracket completion state.
 */
enum BracketState
{
    UNARY, ///< Unary operator set
    BLANK, ///< New bracket openned
    FIRST_OPERAND, ///< First operand set
    BINARY, ///< Binary operator set
    LAST_OPERAND ///< Last operand set
};

Formula* parsePrefix(istream& input)
{
    bool run = true;
    unsigned position = 1;
    Formula* temporary = NULL;
    stack<Composite*> operators;

    while (run)
    {
        char buffer = input.get();
        switch (buffer)
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
                if (!operators.empty())
                {
                    temporary = new Trivial(buffer);
                    while (!operators.empty()
                           && operators.top()->setFirst(temporary))
                    {
                        temporary = operators.top();
                        operators.pop();
                    }
                } else if (position == 1)
                {
                    temporary = new Trivial(buffer);
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    delete temporary;
                    throw RedundantElementException(buffer, position);
                }
                break;
            case '-':
                if (!operators.empty() || position == 1)
                {
                    operators.push(new Unary(buffer));
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    delete temporary;
                    throw RedundantElementException(buffer, position);
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (!operators.empty() || position == 1)
                {
                    operators.push(new Binary(buffer));
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    delete temporary;
                    throw RedundantElementException(buffer, position);
                }
                break;
            case ' ':
            case '\t':
                position--;
                break;
            case '\n':
                run = false;
                break;
            case EOF:
                if (position == 1)
                {
                    run = false;
                } else
                {
                    if (operators.empty())
                    {
                        delete temporary;
                    } else
                    {
                        while (!operators.empty())
                        {
                            delete operators.top();
                            operators.pop();
                        }
                    }
                    throw UnexpectedEOFException();
                }
                break;
            default:
                input.ignore(numeric_limits<streamsize>::max(), '\n');
                if (operators.empty())
                {
                    delete temporary;
                } else
                {
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                }
                throw IllegalCharacterException(buffer, position);
                break;
        }
        position++;
    }
    if (operators.empty())
    {
        return temporary;
    } else
    {
        while (!operators.empty())
        {
            delete operators.top();
            operators.pop();
        }
        throw IncompleteFormulaException();
    }
}

Formula* parseInfix(istream& input)
{
    bool run = true;
    unsigned position = 1;
    Formula* temporary;
    stack<Formula*> formulas;
    stack<Composite*> operators;
    stack<int> states;

    while (run)
    {
        char buffer = input.get();
        switch (buffer)
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
                if (states.empty())
                {
                    if (position == 1)
                    {
                        formulas.push(new Trivial(buffer));
                    } else
                    {
                        input.ignore(numeric_limits<streamsize>::max(), '\n');
                        while (!formulas.empty())
                        {
                            delete formulas.top();
                            formulas.pop();
                        }
                        while (!operators.empty())
                        {
                            delete operators.top();
                            operators.pop();
                        }
                        throw UnexpectedElementException(buffer, position);
                    }
                } else if (states.top() == BLANK || states.top() == BINARY)
                {
                    formulas.push(new Trivial(buffer));
                    states.top()++;
                } else if (states.top() == UNARY)
                {
                    temporary = new Trivial(buffer);
                    do
                    {
                        operators.top()->setFirst(temporary);
                        temporary = operators.top();
                        operators.pop();
                        states.pop();
                    } while (!states.empty() && states.top() == UNARY);
                    formulas.push(temporary);
                    if (states.size())
                    {
                        states.top()++;
                    }
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case '-':
                if (states.empty() && position != 1)
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                    throw RedundantElementException(buffer, position);
                } else if ((states.empty() && position == 1)
                           || states.top() == BLANK
                           || states.top() == BINARY
                           || states.top() == UNARY)
                {
                    states.push(UNARY);
                    operators.push(new Unary(buffer));
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (states.empty())
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (position == 1)
                    {
                        while (!formulas.empty())
                        {
                            delete formulas.top();
                            formulas.pop();
                        }
                        while (!operators.empty())
                        {
                            delete operators.top();
                            operators.pop();
                        }
                        throw UnexpectedElementException(buffer, position);
                    } else
                    {
                        while (!formulas.empty())
                        {
                            delete formulas.top();
                            formulas.pop();
                        }
                        while (!operators.empty())
                        {
                            delete operators.top();
                            operators.pop();
                        }
                        throw RedundantElementException(buffer, position);
                    }
                } else if (states.top() == FIRST_OPERAND)
                {
                    states.top() = BINARY;
                    operators.push(new Binary(buffer));
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case '(':
                if (states.empty())
                {
                    if (position == 1)
                    {
                        states.push(BLANK);
                    } else
                    {
                        input.ignore(numeric_limits<streamsize>::max(), '\n');
                        while (!formulas.empty())
                        {
                            delete formulas.top();
                            formulas.pop();
                        }
                        while (!operators.empty())
                        {
                            delete operators.top();
                            operators.pop();
                        }
                        throw RedundantElementException(buffer, position);
                    }
                } else if (states.top() == BLANK
                           || states.top() == BINARY
                           || states.top() == UNARY)
                {
                    states.push(BLANK);
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case ')':
                if (states.empty())
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                    throw RedundantElementException(buffer, position);
                } else if (states.top() == LAST_OPERAND)
                {
                    states.pop();
                    do
                    {
                        temporary = formulas.top();
                        formulas.pop();
                    } while (!operators.top()->setLast(temporary));
                    formulas.push(operators.top());
                    operators.pop();
                    while (states.size() && states.top() == UNARY)
                    {
                        operators.top()->setFirst(formulas.top());
                        formulas.pop();
                        formulas.push(operators.top());
                        operators.pop();
                        states.pop();
                    }
                    if (states.size())
                    {
                        states.top()++;
                    }
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                    throw UnexpectedElementException(buffer, position);
                }
                break;
            case ' ':
            case '\t':
                position--;
                break;
            case '\n':
                run = false;
                break;
            case EOF:
                if (position == 1)
                {
                    run = false;
                } else
                {
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    while (!operators.empty())
                    {
                        delete operators.top();
                        operators.pop();
                    }
                    throw UnexpectedEOFException();
                }
                break;
            default:
                input.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!formulas.empty())
                {
                    delete formulas.top();
                    formulas.pop();
                }
                while (!operators.empty())
                {
                    delete operators.top();
                    operators.pop();
                }
                throw IllegalCharacterException(buffer, position);
                break;
        }
        position++;
    }
    if (states.empty())
    {
        if (formulas.empty())
        {
            return NULL;
        } else
        {
            return formulas.top();
        }
    } else
    {
        while (!formulas.empty())
        {
            delete formulas.top();
            formulas.pop();
        }
        while (!operators.empty())
        {
            delete operators.top();
            operators.pop();
        }
        throw IncompleteFormulaException();
    }
}

Formula* parsePostfix(istream& input)
{
    bool run = true;
    unsigned position = 1;
    Composite* temporary;
    stack<Formula*> formulas;

    while (run)
    {
        char buffer = input.get();
        switch (buffer)
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
                formulas.push(new Trivial(buffer));
                break;
            case '-':
                if (!formulas.empty())
                {
                    temporary = new Unary(buffer);
                    temporary->setLast(formulas.top());
                    formulas.pop();
                    formulas.push(temporary);
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    throw RedundantElementException(buffer, position);
                }
                break;
            case '.':
            case '+':
            case '>':
            case '=':
                if (formulas.size() > 1)
                {
                    temporary = new Binary(buffer);
                    temporary->setLast(formulas.top());
                    formulas.pop();
                    temporary->setLast(formulas.top());
                    formulas.pop();
                    formulas.push(temporary);
                } else
                {
                    input.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    throw RedundantElementException(buffer, position);
                }
                break;
            case ' ':
            case '\t':
                position--;
                break;
            case '\n':
                run = false;
                break;
            case EOF:
                if (position == 1)
                {
                    run = false;
                } else
                {
                    while (!formulas.empty())
                    {
                        delete formulas.top();
                        formulas.pop();
                    }
                    throw UnexpectedEOFException();
                }
                break;
            default:
                input.ignore(numeric_limits<streamsize>::max(), '\n');
                while (!formulas.empty())
                {
                    delete formulas.top();
                    formulas.pop();
                }
                throw IllegalCharacterException(buffer, position);
                break;
        }
        position++;
    }
    if (formulas.empty())
    {
        return NULL;
    } else if (formulas.size() == 1)
    {
        return formulas.top();
    } else
    {
        while (!formulas.empty())
        {
            delete formulas.top();
            formulas.pop();
        }
        throw IncompleteFormulaException();
    }
}
