#include"ExpressionParser/Expression.h"
#include"ExpressionParser/ExpressionParser.h"
#include<iostream>
int main()
{

    Expression expression = ExpressionParser::parse("1/0");

    std::cout << Expression::isValid(expression) << std::endl;

    std::cout << expression.evaluate(3).has_value();

}