#include "expression/ExpressionTokenizer.h"


// Helper functions for tokenize
namespace {
    bool isUnaryOperator(const std::vector<Token> &tokens, char op) {
        return tokens.empty() ||
               tokens.back().type == TokenType::BinaryOperator ||
               tokens.back().type == TokenType::UnaryOperator ||
               tokens.back().type == TokenType::LeftParen ||
               tokens.back().type == TokenType::Comma;
    }

    ParseResult<Token> parseIdentifier(const std::string &s) {
        if (ExprOps::FUNCTIONS.contains(s)) {
            return Token(TokenType::Function, s);
        }
        if (s == "x" || s == "X") {
            return Token(TokenType::Variable, "x");
        }
        if (s == "pi") {
            return Token(TokenType::Constant, std::to_string(ExprOps::PI));
        }
        if (s == "e") {
            return Token(TokenType::Constant, std::to_string(ExprOps::E));
        }
        return std::unexpected(LexerError{"Invalid variable name or function"});
    }

    ParseResult<Token> parseNumber(const std::string &infix, size_t start, size_t &i) {
        bool dot = false;
        while (i < infix.size() && (std::isdigit(infix[i]) || infix[i] == '.')) {
            if (infix[i] == '.') {
                if (dot) {
                    return std::unexpected(LexerError{"Expected a number, but found multiple dots"});
                }
                dot = true;
            }
            i++;
        }

        std::string str = infix.substr(start, i - start);
        if (str.front() == '.' || str.back() == '.') {
            return std::unexpected(LexerError{"Invalid number format"});
        }

        return Token(TokenType::Constant, str);
    }

    ParseResult<Token> parseOperator(const std::vector<Token> &tokens, char op) {
        bool unary = isUnaryOperator(tokens, op);
        std::string oper = unary ? "u" + std::string(1, op) : std::string(1, op);
        return Token(unary ? TokenType::UnaryOperator : TokenType::BinaryOperator, oper);
    }
} // namespace

ParseResult<std::vector<Token> > ExpressionTokenizer::tokenize(const std::string &infix) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < infix.size()) {
        if (std::isspace(infix[i])) {
            i++;
        } else if (std::isalpha(infix[i])) {
            size_t start = i;
            while (i < infix.size() && std::isalnum(infix[i])) {
                i++;
            }
            auto token = parseIdentifier(infix.substr(start, i - start));
            if (!token) return std::unexpected(token.error());
            tokens.push_back(*token);
        } else if (std::isdigit(infix[i]) || infix[i] == '.') {
            size_t start = i;
            auto token = parseNumber(infix, start, i);
            if (!token) return std::unexpected(token.error());
            tokens.push_back(*token);
        } else if (infix[i] == '+' || infix[i] == '-') {
            auto token = parseOperator(tokens, infix[i]);
            tokens.push_back(*token);
            i++;
        } else if (ExprOps::BINARY_OPERATORS.contains(std::string(1, infix[i]))) {
            tokens.emplace_back(TokenType::BinaryOperator, std::string(1, infix[i]));
            i++;
        } else {
            switch (infix[i]) {
                case ',':
                    tokens.emplace_back(TokenType::Comma, ",");
                    break;
                case '(':
                    tokens.emplace_back(TokenType::LeftParen, "(");
                    break;
                case ')':
                    tokens.emplace_back(TokenType::RightParen, ")");
                    break;
                default:
                    return std::unexpected(LexerError{"Unknown character: " + std::string(1, infix[i])});
            }
            i++;
        }
    }

    return tokens;
}
