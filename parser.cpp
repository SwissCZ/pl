#include <cstdio>

#include "language.hpp"
#include "parser.hpp"

Formula * Parser::parseInPrefix(std::string input)
{
    Operator * output;

    stream << input;

    while ((buffer = stream.get()) != EOF)
    {
        switch (buffer)
        {
            case NEGATION_CHAR:
                stack.push(new UnaryOperator(buffer));
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                stack.push(new BinaryOperator(buffer));
                break;
            default:
                if ('A' <= buffer && buffer <= 'Z')
                {
                    if (((Operator *) stack.top())->addOperandFromLeft(new Preposition(buffer)) == 0)
                    {
                        do
                        {
                            output = (Operator *) stack.top();
                            stack.pop();
                        } while (!stack.empty() && ((Operator *) stack.top())->addOperandFromLeft(output) == 0);
                    }
                }
                break;
        }
    }
    return output;
}

Formula * Parser::parseInInfix(std::string input)
{
    std::stack<Operator *> operatorStack;
    Formula * temp;

    stream << input;

    while ((buffer = stream.get()) != EOF)
    {
        switch (buffer)
        {
            case NEGATION_CHAR:
                operatorStack.push(new UnaryOperator(buffer));
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                operatorStack.push(new BinaryOperator(buffer));
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
                if ('A' <= buffer && buffer <= 'Z')
                {
                    stack.push(new Preposition(buffer));
                }
                break;
        }
    }
    return stack.top();
}

Formula * Parser::parseInPostfix(std::string input)
{
    Operator * output;

    stream << input;

    while ((buffer = stream.get()) != EOF)
    {
        switch (buffer)
        {
            case NEGATION_CHAR:
                output = new UnaryOperator(buffer);
                output->addOperandFromRight(stack.top());
                stack.pop();
                stack.push(output);
                break;
            case CONJUNCTION_CHAR:
            case DISJUNCTION_CHAR:
            case IMPLICATION_CHAR:
            case EQUIVALENCE_CHAR:
                output = new BinaryOperator(buffer);
                output->addOperandFromRight(stack.top());
                stack.pop();
                output->addOperandFromRight(stack.top());
                stack.pop();
                stack.push(output);
                break;
            default:
                if ('A' <= buffer && buffer <= 'Z')
                {
                    stack.push(new Preposition(buffer));
                }
                break;
        }
    }
    return output;
}

