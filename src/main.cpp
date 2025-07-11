#include"Expression.h"
#include"ExpressionParser.h"
#include<iostream>
int main()
{

    Expression expression = ExpressionParser::parse("max(-x+5,x)*sin(x)-min(+5+x,x)*cos(x)");
    std::cout << expression.toString();

}