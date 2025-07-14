#pragma once
#include <stdexcept>
class ExpressionException : public std::exception {
public:
    explicit ExpressionException(const std::string& message);
    const char* what() const noexcept override;
private:
    std::string msg;
};