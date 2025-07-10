#include "Expression.h"


void Expression::add(const Token& token) {
    tokens.push_back(token);
}

std::string Expression::toString() const {
    std::string res;
    for (const Token& token : tokens) {
        res += token.val + " ";
    }
    return res;
}
