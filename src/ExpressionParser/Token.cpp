#include "Token.h"


Token::Token(TokenType type, std::string val) : type(type), val(std::move(val)) {}

