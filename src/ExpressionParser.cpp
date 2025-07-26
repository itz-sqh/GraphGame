#include "ExpressionParser.h"


ParseResult<Expression> ExpressionParser::parse(const std::string &infix) {
    auto tokens = tokenize(infix);
    if (!tokens) return std::unexpected(tokens.error());

    auto expr = shuntingYard(tokens.value());
    if (!expr) return std::unexpected(expr.error());

    if (!expr->isValid()) return std::unexpected(ValidationError("Expression is not valid"));

    return expr;

}

std::optional<int> ExpressionParser::getPrecedence(const Token& token) {
    switch (token.type) {
        case TokenType::UnaryOperator: {
            if (auto it = Constants::UNARY_OPERATORS.find(token.val); it != Constants::UNARY_OPERATORS.end()) {
                return it->second.precedence;
            }
            break;
        }
        case TokenType::BinaryOperator: {
            if (auto it = Constants::BINARY_OPERATORS.find(token.val); it != Constants::BINARY_OPERATORS.end()) {
                return it->second.precedence;
            }
            break;
        }
        default:
            break;
    }
    return std::nullopt;
}

ParseResult<std::vector<Token>> ExpressionParser::tokenize(const std::string& infix) {
    std::vector<Token> tokens;
    int i = 0;
    while (i < infix.size()) {
        if (std::isspace(infix[i])) {
            i++;
            continue;
        }
        if (std::isalpha(infix[i])) {
            int start = i;
            while (i < infix.size() && std::isalnum(infix[i])) i++;
            std::string s = infix.substr(start, i - start);

            if (Constants::FUNCTIONS.contains(s)) {
                tokens.emplace_back(TokenType::Function,s);
            } else if (s == "x" || s == "X") {
                tokens.emplace_back(TokenType::Variable,"x");
            } else if (s == "pi") {
                tokens.emplace_back(TokenType::Constant, std::to_string(Constants::PI));
            }
            else if (s == "e") {
                tokens.emplace_back(TokenType::Constant, std::to_string(Constants::E));
            }
            else return std::unexpected(LexerError{"Invalid variable name or function"});
            continue;
        }
        if (std::isdigit(infix[i]) || infix[i] == '.') {
            int start = i;
            bool dot = infix[i] == '.';
            i++;
            while (i < infix.size() && (std::isdigit(infix[i]) || infix[i] == '.')) {
                if (infix[i] == '.') {
                    if (dot) return std::unexpected(LexerError{"Expected a number, but found 2 dots"});
                    dot = true;
                }
                i++;
            }
            if (std::string num = infix.substr(start, i - start); num[0] == '.') return std::unexpected(LexerError{"Expected a number, but found dot"});
            tokens.emplace_back(TokenType::Constant,infix.substr(start, i - start));
            continue;
        }
        if (infix[i] == '+' || infix[i] == '-') {
            bool isUnary = tokens.empty() || tokens.back().type == TokenType::BinaryOperator ||
                tokens.back().type == TokenType::UnaryOperator ||
                    tokens.back().type == TokenType::LeftParen ||
                        tokens.back().type == TokenType::Comma;
            if (isUnary)
                tokens.emplace_back(TokenType::UnaryOperator,"u"+std::string(1,infix[i]));
            else
                tokens.emplace_back(TokenType::BinaryOperator,std::string(1,infix[i]));
            i++;
            continue;
        }
        if (Constants::BINARY_OPERATORS.contains(std::string(1, infix[i]))) {
            tokens.emplace_back(TokenType::BinaryOperator, std::string(1, infix[i]));
            i++;
            continue;
        }
        if (infix[i] == ',') {
            tokens.emplace_back(TokenType::Comma,",");
            i++;
            continue;
        }
        if (infix[i] == '(') {
            tokens.emplace_back(TokenType::LeftParen,"(");
            i++;
            continue;
        }
        if (infix[i] == ')') {
            tokens.emplace_back(TokenType::RightParen,")");
            i++;
            continue;
        }
        return std::unexpected(LexerError{"Unknown character: " + infix[i] });

    }
    return tokens;
}

ParseResult<Expression> ExpressionParser::shuntingYard(const std::vector<Token>& tokens) {
    if (tokens.empty()) return std::unexpected(ParserError{"Expected at least one token"});
    Expression res;
    std::stack<Token> st;


    for (const Token& token : tokens) {
        switch (token.type) {
            case TokenType::Constant:
            case TokenType::Variable:
                res.add(token);
                break;

            case TokenType::BinaryOperator: {
                while (!st.empty() &&
                      (st.top().type == TokenType::BinaryOperator ||
                       st.top().type == TokenType::UnaryOperator) &&
                      (getPrecedence(st.top()) > getPrecedence(token) ||
                      (getPrecedence(st.top()) == getPrecedence(token) &&
                       Constants::BINARY_OPERATORS.at(token.val).associative))) {
                    res.add(st.top());
                    st.pop();
                }
                st.push(token);
                break;
            }
            case TokenType::Function:
            case TokenType::UnaryOperator:
            case TokenType::LeftParen:
                st.push(token);
                break;

            case TokenType::RightParen:
                while (!st.empty() && st.top().type != TokenType::LeftParen) {
                    res.add(st.top());
                    st.pop();
                }
                if (st.empty()) return std::unexpected(ParserError{"Mismatched parentheses"});
                st.pop();

                if (!st.empty() && st.top().type == TokenType::Function) {
                    res.add(st.top());
                    st.pop();
                }
                break;

            case TokenType::Comma:
                while (!st.empty() && st.top().type != TokenType::LeftParen) {
                    res.add(st.top());
                    st.pop();
                }
                if (st.empty()) return std::unexpected(ParserError{"Mismatched parentheses"});
                break;

            default:
                break;
        }
    }

    while (!st.empty()) {
        if (st.top().type == TokenType::LeftParen) {
            return std::unexpected(ParserError{"Mismatched parentheses"});
        }
        res.add(st.top());
        st.pop();
    }

    return ParseResult<Expression>(res);
}
