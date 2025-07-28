#pragma once
#include <string>
#include <vector>
#include "Expression.h"
#include "Token.h"
#include <stdexcept>
#include "ExpressionOperators.h"
#include<stack>
#include"ExpressionTokenizer.h"

class ExpressionParser {
public:
    static ParseResult<Expression> parse(const std::string& infix);

private:
    static ParseResult<Expression> shuntingYard(const std::vector<Token>& tokens);
};