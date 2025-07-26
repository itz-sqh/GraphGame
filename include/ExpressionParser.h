#pragma once
#include <string>
#include <vector>
#include "Expression.h"
#include "Token.h"
#include <stdexcept>
#include "constants.h"
#include<stack>
#include "ExpressionException.h"

class ExpressionParser {
public:
    static Expression parse(const std::string& infix);

    static std::optional<std::vector<Token>> tokenize(const std::string& infix);


private:

    static std::optional<Expression> shuntingYard(const std::vector<Token>& tokens);
    static std::optional<int> getPrecedence(const Token& token);
};