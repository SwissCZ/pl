
#include <stack>

#include "parse.hpp"
#include "language.hpp"

Formula * parsePrefix(std::string input)
{
    std::stack<Operator *> stack;
    Operator * output;

    for (unsigned i = 0; i < input.length(); i++)
    {
        switch (input[i])
        {
            case NEGATION_CHAR:
                stack.push(new UnaryOperator(input[i]));
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                stack.push(new BinaryOperator(input[i]));
                break;
            default:
                if ('A' <= input[i] && input[i] <= 'Z')
                {
                    if (stack.top()->addOperandFromLeft(new Preposition(input[i])) == 0)
                    {
                        do
                        {
                            output = stack.top();
                            stack.pop();
                        } while (!stack.empty() && (stack.top())->addOperandFromLeft(output) == 0);
                    }
                }
                break;
        }
    }
    return output;
}

Formula * parseInfix(std::string input)
{
    std::stack<Formula *> stack;
    std::stack<Operator *> operatorStack;
    Formula * temp;

    for (unsigned i = 0; i < input.length(); i++)
    {
        switch (input[i])
        {
            case NEGATION_CHAR:
                operatorStack.push(new UnaryOperator(input[i]));
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                operatorStack.push(new BinaryOperator(input[i]));
                break;
            case ')':
                do
                {
                    temp = stack.top();
                    stack.pop();
                } while (operatorStack.top()->addOperandFromRight(temp) > 0);
                stack.push(operatorStack.top());
                operatorStack.pop();
                break;
            default:
                if ('A' <= input[i] && input[i] <= 'Z')
                {
                    stack.push(new Preposition(input[i]));
                }
                break;
        }
    }
    return stack.top();
}

Formula * parsePostfix(std::string input)
{
    std::stack<Formula *> stack;
    Operator * temp;

    for (unsigned i = 0; i < input.length(); i++)
    {
        switch (input[i])
        {
            case NEGATION_CHAR:
                temp = new UnaryOperator(input[i]);
                temp->addOperandFromRight(stack.top());
                stack.pop();
                stack.push(temp);
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                temp = new BinaryOperator(input[i]);
                temp->addOperandFromRight(stack.top());
                stack.pop();
                temp->addOperandFromRight(stack.top());
                stack.pop();
                stack.push(temp);
                break;
            default:
                if ('A' <= input[i] && input[i] <= 'Z')
                {
                    stack.push(new Preposition(input[i]));
                }
                break;
        }
    }
    return stack.top();
}

