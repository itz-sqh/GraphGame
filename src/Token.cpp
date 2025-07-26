#include "Token.h"


Token::Token(TokenType type, std::string val) : type(type), val(std::move(val)) {}

bool Token::operator==(const Token& other) const {
    return type == other.type && val == other.val;
}

