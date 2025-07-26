#pragma once
#include<vector>
#include "Token.h"
#include<optional>
#include "constants.h"
#include<stack>


class Expression {
public:
    explicit Expression(const std::vector<Token> &tokens);

    explicit Expression(const Expression& expression);

    Expression() = default;

    void add(const Token& token);

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] static bool isEqual(const Expression& lhs, const Expression& rhs);

    [[nodiscard]] std::optional<float> evaluate(float x) const;

private:
    std::vector<Token> tokens;

};
