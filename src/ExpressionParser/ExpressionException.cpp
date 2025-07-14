#include "ExpressionException.h"

ExpressionException::ExpressionException(const std::string &message) : msg(message) {}

const char* ExpressionException::what() const noexcept {
    return msg.c_str();
}


