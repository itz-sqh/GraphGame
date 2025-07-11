#pragma once
#include <vector>

#include "Token.h"
#include<optional>


class Expression {
public:

    void add(const Token& token);

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] static bool isValid(const Expression& expression);

    [[nodiscard]] std::optional<double> evaluate(double x) const;

private:
    std::vector<Token> tokens;

};
