#include <cstdio>
#include <sstream>
#include <stack>

#include "formula.hpp"
#include "language.hpp"
#include "parser.hpp"

Formula * Parser::parseInPrefix(std::string input) const
{
    std::stringstream stream;
    std::stack<Formula *> stack;
    char buffer;
    Operator * output;

    stream << input;

    while ((buffer = stream.get()) != EOF)
    {
        if (buffer == NEGATION_CHAR || buffer == CONJUNCTION_CHAR || buffer == DISJUNCTION_CHAR || buffer == IMPLICATION_CHAR || buffer == EQUIVALENCE_CHAR)
        {
            stack.push(new Operator(buffer));
        } else if ('A' <= buffer && buffer <= 'Z')
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
    }
    return output;
}

Formula * Parser::parseInInfix(std::string input) const
{
    std::stringstream stream;
    std::stack<Formula *> stack;
    std::stack<Operator *> operatorStack;
    int brackets = 0;
    char buffer;
    Operator * output;
    Formula * tempOperand;

    stream << input;

    while ((buffer = stream.get()) != EOF)
    {
        if (buffer == NEGATION_CHAR || buffer == CONJUNCTION_CHAR || buffer == DISJUNCTION_CHAR || buffer == IMPLICATION_CHAR || buffer == EQUIVALENCE_CHAR)
        {
            operatorStack.push(new Operator(buffer));
        } else if ('A' <= buffer && buffer <= 'Z')
        {
            stack.push(new Preposition(buffer));
        } else if (buffer == ')')
        {
            do
            {
                tempOperand = stack.top();
                stack.pop();
            } while (operatorStack.top()->addOperandFromRight(tempOperand) > 0);
            stack.push(operatorStack.top());
            operatorStack.pop();
        }
    }
    return stack.top();
}

Formula * Parser::parseInPostfix(std::string input) const
{
    std::stringstream stream;
    std::stack<Formula *> stack;
    char buffer;
    Operator * output;
    Formula * temp;

    stream << input;

    while ((buffer = stream.get()) != EOF)
    {
        if (buffer == NEGATION_CHAR || buffer == CONJUNCTION_CHAR || buffer == DISJUNCTION_CHAR || buffer == IMPLICATION_CHAR || buffer == EQUIVALENCE_CHAR)
        {
            output = new Operator(buffer);
            do
            {
                temp = stack.top();
                stack.pop();
            } while (output->addOperandFromRight(temp) > 0);
            stack.push(output);
        } else if ('A' <= buffer && buffer <= 'Z')
        {
            stack.push(new Preposition(buffer));
        }
    }
    return output;
}

