#pragma once
#include<string>
#include<utility>
#include <boost/serialization/access.hpp>

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
    TokenType type{};
    std::string val;

    Token(TokenType type, std::string val);

    Token() = default;

    bool operator==(const Token& other) const;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int) {
        ar & type & val;
    }
};