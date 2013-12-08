#include <cstdio>
#include <sstream>
#include <stack>
#include <iostream>

#include "connective.hpp"
#include "formula.hpp"
#include "language.hpp"
#include "parser.hpp"

Node * Parser::parse(std::string input, Notation notation) const
{
    std::stringstream stream;
    char buffer;

    // postfix
    std::stack<Node *> stack;

    // prefix
    Operator * temp;

    stream << input;

    switch (notation)
    {
        case PREFIX:
            while ((buffer = stream.get()) != EOF)
            {
                switch (buffer)
                {
                    case NEGATION_CHAR:
                        stack.push(new UnaryOperator(NEGATION));
                        break;
                    case CONJUNCTION_CHAR:
                        std::cout << (char) CONJUNCTION <<std::endl;
                        stack.push(new BinaryOperator(CONJUNCTION));
                        break;
                    case DISJUNCTION_CHAR:
                        stack.push(new BinaryOperator(DISJUNCTION));
                        break;
                    case IMPLICATION_CHAR:
                        stack.push(new BinaryOperator(IMPLICATION));
                        break;
                    case EQUIVALENCE_CHAR:
                        stack.push(new BinaryOperator(EQUIVALENCE));
                        break;
                    default:
                        if ('A' <= buffer && buffer <= 'Z')
                        {
                            if (((Operator *) stack.top())->addOperand(new Preposition(buffer)) == 0)
                            {
                                do
                                {
                                    temp = (Operator *) stack.top();
                                    stack.pop();
                                } while (!stack.empty() && ((Operator *) stack.top())->addOperand(temp) == 0);
                            }
                        }
                        break;
                }
            }
            break;
        case INFIX:
            break;
        case POSTFIX:
            break;
    }
    return temp;
}