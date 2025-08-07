#pragma once

#include<string>
#include<expected>
#include<variant>

struct LexerError {
    std::string msg;
};

struct ParserError {
    std::string msg;
};

struct ValidationError {
    std::string msg;
};

using ParseError = std::variant<LexerError, ParserError, ValidationError>;

template<typename T>
using ParseResult = std::expected<T, ParseError>;
