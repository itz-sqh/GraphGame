#pragma once
#include<string>
#include<utility>

enum class TokenType {
    Constant,
    Variable,
    BinaryOperator,
    UnaryOperator,
    Function,
    LeftParen,
    RightParen,
    Comma
};
class Token {
public:
    TokenType type;
    std::string val;

    Token(TokenType type, std::string val);
};