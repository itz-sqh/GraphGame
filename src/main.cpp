#include"Expression.h"
#include"ExpressionParser.h"
#include<iostream>
int main()
{

    Expression expression = ExpressionParser::parse("sqrt(4)*sqrt(9)+2*(x+3)*log(x)");
    std::cout << expression.toString();

}