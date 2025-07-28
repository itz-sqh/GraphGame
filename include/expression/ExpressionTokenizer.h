#pragma once
#include <vector>
#include "ExpressionErrors.h"
#include "Token.h"
#include"ExpressionOperators.h"

class ExpressionTokenizer {
    public:
    static ParseResult<std::vector<Token>> tokenize(const std::string& infix);
};
