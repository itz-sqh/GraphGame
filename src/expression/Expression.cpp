#include "expression/Expression.h"


// Helper functions for evaluate
namespace {
    bool processConstant(const Token &token, std::stack<float> &st) {
        float value;

        auto [ptr, ec] = std::from_chars(token.val.data(), token.val.data() + token.val.size(), value);

        if (ec != std::errc() || ptr != token.val.data() + token.val.size()) {
            return false;
        }

        st.push(value);
        return true;
    }

    bool processVariable(const float x, std::stack<float> &st) {
        st.push(x);
        return true;
    }

    bool processUnaryOperator(const Token &token, std::stack<float> &st) {
        if (st.empty()) return false;

        const auto oper = ExprOps::UNARY_OPERATORS.find(token.val);
        if (oper == ExprOps::UNARY_OPERATORS.end()) {
            return false;
        }

        const float operand = st.top();
        st.pop();

        const float res = oper->second.operation(operand);
        if (std::isinf(res) || std::isnan(res)) {
            return false;
        }

        st.push(res);
        return true;
    }

    bool processBinaryOperator(const Token &token, std::stack<float> &st) {
        if (st.size() < 2) return false;

        auto oper = ExprOps::BINARY_OPERATORS.find(token.val);
        if (oper == ExprOps::BINARY_OPERATORS.end()) {
            return false;
        }

        const float b = st.top();
        st.pop();
        const float a = st.top();
        st.pop();

        const float res = oper->second.operation(a, b);
        if (std::isinf(res) || std::isnan(res)) {
            return false;
        }

        st.push(res);
        return true;
    }

    bool processFunction(const Token &token, std::stack<float> &st) {
        const auto &func = ExprOps::FUNCTIONS.find(token.val);

        if (func == ExprOps::FUNCTIONS.end()) return false;

        if (st.size() < func->second.argCount) return false;

        std::vector<float> args(func->second.argCount);
        for (int i = func->second.argCount - 1; i >= 0; --i) {
            args[i] = st.top();
            st.pop();
        }

        const float res = func->second.operation(args);
        if (std::isinf(res) || std::isnan(res)) return false;

        st.push(res);
        return true;
    }
}


void Expression::add(const Token &token) {
    m_tokens.push_back(token);
}

std::string Expression::toString() const {
    if (!this->isValid()) return "";

    std::stack<std::string> st;

    for (const Token &token: m_tokens) {
        switch (token.type) {
            case TokenType::Constant:
            case TokenType::Variable:
                st.push(token.val);
                break;

            case TokenType::UnaryOperator: {
                std::string operand = st.top();
                st.pop();
                std::string op_symbol = token.val.substr(1);
                st.push(op_symbol + operand);
                break;
            }

            case TokenType::BinaryOperator: {
                std::string right = st.top();
                st.pop();
                std::string left = st.top();
                st.pop();

                st.push("(" + left + " " + token.val + " " + right + ")");
                break;
            }

            case TokenType::Function: {
                auto it = ExprOps::FUNCTIONS.find(token.val);
                int argCount = it->second.argCount;

                std::vector<std::string> args(argCount);
                for (int i = argCount - 1; i >= 0; --i) {
                    args[i] = st.top();
                    st.pop();
                }

                std::string args_str;
                for (int i = 0; i < argCount; ++i) {
                    if (i != 0) args_str += ", ";
                    args_str += args[i];
                }

                st.push(token.val + "(" + args_str + ")");
                break;
            }

            default:
                break;
        }
    }

    std::string res = st.top();

    if (res.size() > 1 && res.front() == '(' && res.back() == ')')
        res = res.substr(1, res.size() - 2);
    return res;
}

bool Expression::isValid() const {
    int stackSize = 0;
    for (const Token &token: m_tokens) {
        switch (token.type) {
            case TokenType::Constant:
            case TokenType::Variable:
                stackSize++;
                break;

            case TokenType::UnaryOperator:
                if (stackSize < 1) return false;
                break;

            case TokenType::BinaryOperator:
                if (stackSize < 2) return false;
                stackSize--;
                break;

            case TokenType::Function: {
                auto it = ExprOps::FUNCTIONS.find(token.val);
                if (it == ExprOps::FUNCTIONS.end()) return false;
                const int argc = it->second.argCount;
                if (stackSize < argc) return false;
                stackSize = stackSize - argc + 1;
                break;
            }

            default:
                return false;
        }
    }
    // There should be only 1 variable by the end of evaluating
    return stackSize == 1;
}


std::optional<float> Expression::evaluate(const float x) const {
    if (!this->isValid())
        return std::nullopt;

    std::stack<float> st;

    for (const Token &token: m_tokens) {
        bool success = false;

        switch (token.type) {
            case TokenType::Constant:
                success = processConstant(token, st);
                break;

            case TokenType::Variable:
                success = processVariable(x, st);
                break;

            case TokenType::UnaryOperator:
                success = processUnaryOperator(token, st);
                break;

            case TokenType::BinaryOperator:
                success = processBinaryOperator(token, st);
                break;

            case TokenType::Function:
                success = processFunction(token, st);
                break;

            default:
                return std::nullopt;
        }
        if (!success) return std::nullopt;
    }

    return st.size() == 1 ? std::optional(st.top()) : std::nullopt;
}


bool Expression::isEqual(const Expression &lhs, const Expression &rhs) {
    return lhs.m_tokens == rhs.m_tokens;
}

Expression::Expression(const std::vector<Token> &tokens) {
    for (const Token &token: tokens) {
        add(token);
    }
}

Expression::Expression(const Expression &expression) {
    m_tokens = expression.m_tokens;
}
