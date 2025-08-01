#include "expression/Expression.h"



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

bool Expression::isValid() const {
    int size = 0;
    for (const Token& token : tokens) {
        switch (token.type) {
            case TokenType::Constant:
            case TokenType::Variable:
                size++;
                break;
            case TokenType::UnaryOperator:
                if (size < 1) return false;
                break;
            case TokenType::BinaryOperator:
                if (size < 2) return false;
                size--;
                break;
            case TokenType::Function: {
                auto it = Constants::FUNCTIONS.find(token.val);
                if (it == Constants::FUNCTIONS.end()) return false;
                const int argc = it->second.argCount;
                if (size < argc) return false;
                size = size - argc + 1;
                break;
            }
            default:
                return false;
        }
    }
    return size == 1;
}

std::optional<float> Expression::evaluate(const float x) const {
    if (!this->isValid())
        return std::nullopt;

    std::stack<double> st;

    for (const Token& token : tokens) {
        try {
            switch (token.type) {
                case TokenType::Constant:
                    st.push(std::stod(token.val));
                    break;

                case TokenType::Variable:
                    st.push(x);
                    break;

                case TokenType::UnaryOperator: {
                    if (st.empty()) return std::nullopt;
                    const auto& op = Constants::UNARY_OPERATORS.find(token.val);
                    if (op == Constants::UNARY_OPERATORS.end()) return std::nullopt;

                    const double operand = st.top();
                    st.pop();
                    auto res = op->second.operation(operand);
                    if (std::isinf(res) || std::isnan(res)) return std::nullopt;
                    st.push(res);
                    break;
                }

                case TokenType::BinaryOperator: {
                    if (st.size() < 2) return std::nullopt;
                    const auto& op = Constants::BINARY_OPERATORS.find(token.val);
                    if (op == Constants::BINARY_OPERATORS.end()) return std::nullopt;

                    const double b = st.top(); st.pop();
                    const double a = st.top(); st.pop();

                    const double res = op->second.operation(a,b);
                    if (std::isinf(res) || std::isnan(res)) return std::nullopt;
                    st.push(res);
                    break;
                }

                case TokenType::Function: {
                    const auto& func = Constants::FUNCTIONS.find(token.val);
                    if (func == Constants::FUNCTIONS.end()) return std::nullopt;
                    if (st.size() < func->second.argCount) return std::nullopt;

                    std::vector<double> args(func->second.argCount);
                    for (int i = func->second.argCount - 1; i >= 0; --i) {
                        args[i] = st.top();
                        st.pop();
                    }

                    const double res = func->second.operation(args);
                    if (std::isinf(res) || std::isnan(res)) return std::nullopt;
                    st.push(res);
                    break;
                }

                default:
                    return std::nullopt;
            }
        } catch (...) {
            return std::nullopt;
        }
    }

    return st.size() == 1 ? std::optional<double>(st.top()) : std::nullopt;
}


bool Expression::isEqual(const Expression& lhs, const Expression& rhs) {
    return lhs.tokens == rhs.tokens;
}
Expression::Expression(const std::vector<Token> &tokens) {
    for (const Token& token : tokens) {
        add(token);
    }
}
Expression::Expression(const Expression &expression) {
    tokens = expression.tokens;
}

