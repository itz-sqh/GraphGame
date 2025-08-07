#pragma once
#include <vector>
#include "Token.h"
#include <optional>
#include "ExpressionOperators.h"
#include <stack>
#include <charconv>


class Expression {
public:
    explicit Expression(const std::vector<Token> &tokens);

    Expression(const Expression &expression);

    Expression() = default;

    void add(const Token &token);

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] static bool isEqual(const Expression &lhs, const Expression &rhs);

    [[nodiscard]] std::optional<float> evaluate(float x) const;

private:
    std::vector<Token> m_tokens;
};
