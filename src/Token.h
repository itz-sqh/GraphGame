#pragma once
#include<string>
#include<utility>

enum class TokenType {
    Constant,
    Variable,
    Operator,
    Function,
    LeftParen,
    RightParen
};
class Token {
public:
    TokenType type;
    std::string val;

    Token(TokenType type, std::string val);
};