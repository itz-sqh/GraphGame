#include"ExpressionParser/Expression.h"
#include"ExpressionParser/ExpressionParser.h"
#include<iostream>
int main()
{

    Expression expression = ExpressionParser::parse("max(1,x)*(x-3)/(x-3)");

    std::cout << Expression::isValid(expression) << std::endl;

    std::cout << expression.evaluate(3).value() << std::endl;

}