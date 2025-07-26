#pragma once
#include <string>
#include <vector>
#include "Expression.h"
#include "Token.h"
#include <stdexcept>
#include "constants.h"
#include<stack>
#include"ExpressionErrors.h"

class ExpressionParser {
public:
    static ParseResult<Expression> parse(const std::string& infix);

    static ParseResult<std::vector<Token>> tokenize(const std::string& infix);

private:

    static ParseResult<Expression> shuntingYard(const std::vector<Token>& tokens);
    static std::optional<int> getPrecedence(const Token& token);
};