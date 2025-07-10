#pragma once
#include <vector>

#include "Token.h"


class Expression {
public:

    void add(const Token& token);

    [[nodiscard]] std::string toString() const;

private:
    std::vector<Token> tokens;

};
