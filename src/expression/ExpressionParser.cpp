#include "expression/ExpressionParser.h"


// Helper functions for shuntingYard
namespace {

std::optional<int> getPrecedence(const Token& token) {
    switch (token.type) {
        case TokenType::UnaryOperator:
            if (auto it = ExprOps::UNARY_OPERATORS.find(token.val); it != ExprOps::UNARY_OPERATORS.end()) {
                return it->second.precedence;
            }
            break;
        case TokenType::BinaryOperator:
            if (auto it = ExprOps::BINARY_OPERATORS.find(token.val); it != ExprOps::BINARY_OPERATORS.end()) {
                return it->second.precedence;
            }
            break;
        default:
            break;
    }
    return std::nullopt;
}

ParseResult<Expression> processBinaryOperator(
    const Token& token,
    std::stack<Token>& st,
    Expression& res
) {
    while (!st.empty() &&
          (st.top().type == TokenType::BinaryOperator ||
           st.top().type == TokenType::UnaryOperator) &&
          (getPrecedence(st.top()) > getPrecedence(token) ||
          (getPrecedence(st.top()) == getPrecedence(token) &&
           ExprOps::BINARY_OPERATORS.at(token.val).associative))) {
        res.add(st.top());
        st.pop();
    }
    st.push(token);
    return {};
}

ParseResult<Expression> processRightParen(
    std::stack<Token>& st,
    Expression& res
) {
    while (!st.empty() && st.top().type != TokenType::LeftParen) {
        res.add(st.top());
        st.pop();
    }
    if (st.empty()) {
        return std::unexpected(ParserError{"Mismatched parentheses"});
    }
    st.pop();

    if (!st.empty() && st.top().type == TokenType::Function) {
        res.add(st.top());
        st.pop();
    }
    return {};
}

ParseResult<Expression> processComma(
    std::stack<Token>& st,
    Expression& res
) {
    while (!st.empty() && st.top().type != TokenType::LeftParen) {
        res.add(st.top());
        st.pop();
    }
    if (st.empty()) {
        return std::unexpected(ParserError{"Mismatched parentheses"});
    }
    return {};
}

ParseResult<Expression> processRemainingTokens(
    std::stack<Token>& st,
    Expression& res
) {
    while (!st.empty()) {
        if (st.top().type == TokenType::LeftParen) {
            return std::unexpected(ParserError{"Mismatched parentheses"});
        }
        res.add(st.top());
        st.pop();
    }
    return {};
}

}

ParseResult<Expression> ExpressionParser::parse(const std::string &infix) {
    auto tokens = ExpressionTokenizer::tokenize(infix);
    if (!tokens) return std::unexpected(tokens.error());

    auto expr = shuntingYard(tokens.value());
    if (!expr) return std::unexpected(expr.error());

    if (!expr->isValid()) {
        return std::unexpected(ValidationError("Expression is not valid"));
    }

    return expr;
}

ParseResult<Expression> ExpressionParser::shuntingYard(const std::vector<Token>& tokens) {
    if (tokens.empty()) {
        return std::unexpected(ParserError{"Expected at least one token"});
    }

    Expression res;
    std::stack<Token> st;

    for (const Token& token : tokens) {
        ParseResult<Expression> success;

        switch (token.type) {
            case TokenType::Constant:
            case TokenType::Variable:
                res.add(token);
                break;

            case TokenType::BinaryOperator:
                success = processBinaryOperator(token, st, res);
                if (!success) return success;
                break;

            case TokenType::Function:
            case TokenType::UnaryOperator:
            case TokenType::LeftParen:
                st.push(token);
                break;

            case TokenType::RightParen:
                success = processRightParen(st, res);
                if (!success) return success;
                break;

            case TokenType::Comma:
                success = processComma(st, res);
                if (!success) return success;
                break;

            default:
                break;
        }
    }

    auto success = processRemainingTokens(st, res);
    if (!success) return success;

    return {res};
}