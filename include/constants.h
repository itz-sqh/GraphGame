#pragma once
#include<string>
#include<map>
#include<functional>
#include<cmath>



struct BinaryOperator {
    int precedence;
    bool associative;
    std::function<double(double,double)> operation;
};
struct UnaryOperator {
    int precedence;
    std::function<double(double)> operation;
};
struct Function {
    int argCount;
    std::function<double(const std::vector<double>&)> operation;
};
namespace Constants {
    constexpr double PI = 3.141592653589793;
    constexpr double E 	= 2.71828182845903;
    const std::map<std::string, BinaryOperator> BINARY_OPERATORS = {
        {"+", {2, true, [](const double a, const double b) { return a + b; }}},
        {"-", {2, true, [](const double a, const double b) { return a - b; }}},
        {"*", {3, true, [](const double a, const double b) { return a * b; }}},
        {"/", {3, true, [](const double a, const double b) { return a / b; }}},
        {"^", {4, false, [](const double a, const double b) { return std::pow(a, b); }}}
    };
    const std::map<std::string, UnaryOperator> UNARY_OPERATORS = {
        {"u+", {4,[](const double a) { return a; }}},
        {"u-", {4,[](const double a) { return -a; }}}
    };
    const std::map<std::string, Function> FUNCTIONS = {
        {"sin", {1, [](const std::vector<double>& args) { return std::sin(args[0]); }}},
        {"cos", {1, [](const std::vector<double>& args) { return std::cos(args[0]); }}},
        {"tan", {1, [](const std::vector<double>& args) { return std::tan(args[0]); }}},
        {"exp", {1, [](const std::vector<double>& args) { return std::exp(args[0]); }}},
        {"log", {1, [](const std::vector<double>& args) { return std::log(args[0]); }}},
        {"sqrt", {1, [](const std::vector<double>& args) { return std::sqrt(args[0]); }}},
        {"max", {2, [](const std::vector<double>& args) { return std::max(args[0], args[1]); }}},
        {"min", {2, [](const std::vector<double>& args) { return std::min(args[0], args[1]); }}},
        {"abs", {2, [](const std::vector<double>& args) { return std::abs(args[0]); }}},
        {"sign", {2, [](const std::vector<double>& args) { return (args[0]==0 ? 0:args[0]/std::abs(args[0])); }}}
    };

}
