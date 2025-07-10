#include "ExpressionParser.h"

#include <stdexcept>

#include "constants.h"

#include<stack>


Expression ExpressionParser::parse(const std::string &infix) {
    std::vector<Token> tokens = tokenize(infix);
    return shuntingYard(tokens);
}

std::vector<Token> ExpressionParser::tokenize(const std::string& infix) {
    std::vector<Token> tokens;
    for (int i = 0; i < infix.size();) {
        if (std::isspace(infix[i])) {
            i++;
            continue;
        }
        if (std::isalpha(infix[i])) {
            int start = i;
            while (i < infix.size() && std::isalnum(infix[i])) i++;
            std::string s = infix.substr(start, i - start);

            if (FUNCTIONS.contains(s)) {
                tokens.emplace_back(TokenType::Function,s);
            } else {
                tokens.emplace_back(TokenType::Variable,s);
            }
            continue;
        }
        if (std::isdigit(infix[i]) || infix[i] == '.') {
            int start = i;
            bool dot = infix[i] == '.';
            i++;
            while (i < infix.size() && (std::isdigit(infix[i]) || infix[i] == '.')) {
                if (infix[i] == '.') {
                    if (dot) throw std::runtime_error("Expected a number, but found 2 dots");
                    dot = true;
                }
                i++;
            }
            std::string num = infix.substr(start, i - start);
            if (num == ".") throw std::runtime_error("Expected a number, but found dot");
            tokens.emplace_back(TokenType::Constant,infix.substr(start, i - start));
            continue;
        }
        if (OPERATOR_IS_ASSOCIATIVE.contains(std::string(1,infix[i]))) {
            tokens.emplace_back(TokenType::Operator,std::string(1,infix[i]));
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
        throw std::runtime_error("Unknown character: "  + infix[i]);

    }
    return tokens;
}

Expression ExpressionParser::shuntingYard(const std::vector<Token>& tokens) {
    Expression res;
    std::stack<Token> st;
    for (const Token& token : tokens) {
        switch (token.type) {
            case TokenType::Constant:
            case TokenType::Variable:
                res.add(token);
                break;
            case TokenType::Function:
                st.push(token);
                break;
            case TokenType::Operator: {
                while (!st.empty() && st.top().type == TokenType::Operator &&
                       ((OPERATOR_PRECEDENCE.at(st.top().val) > OPERATOR_PRECEDENCE.at(token.val)) ||
                        (OPERATOR_PRECEDENCE.at(st.top().val) == OPERATOR_PRECEDENCE.at(token.val) &&
                         OPERATOR_IS_ASSOCIATIVE.at(token.val)))) {
                    res.add(st.top());
                    st.pop();
                         }
                st.push(token);
                break;
            }
            case TokenType::LeftParen:
                st.push(token);
                break;
            case TokenType::RightParen:
                while (!st.empty() && st.top().type != TokenType::LeftParen) {
                    res.add(st.top());
                    st.pop();
                }
                if (st.empty()) throw std::runtime_error("Mismatched parentheses");
                st.pop();

                if (!st.empty() && st.top().type == TokenType::Function) {
                    res.add(st.top());
                    st.pop();
                }
                break;
            default:
                break;

        }
    }
    while (!st.empty()) {
        if (st.top().type == TokenType::LeftParen) {
            throw std::runtime_error("Mismatched parentheses");
        }
        res.add(st.top());
        st.pop();
    }

    return res;
}

