#define BOOST_TEST_MODULE ExpressionEvaluationTest
#include<boost/test/unit_test.hpp>
#include"ExpressionParser.h"
#include "Game.h"
#include "GameConstants.h"

void test_expression(const std::string &infix, const std::function<float(float)> &func, float from, float to,
                     float step,
                     float eps = GameConstants::EPS) {
    auto expr = ExpressionParser::parse(infix);
    if (!expr.has_value()) return;
    for (float x = from; x <= to; x += step) {
        auto res = expr.value().evaluate(x);
        BOOST_TEST_REQUIRE(res.has_value());
        BOOST_CHECK_CLOSE(res.value(), func(x), eps);
    }
}

BOOST_AUTO_TEST_SUITE(ExpressionEvaluationTest)

    BOOST_AUTO_TEST_CASE(basic_arithmetic) {
        test_expression("x + 5", [](float x) { return x + 5; }, -10, 10, 1);

        test_expression("x - 3", [](float x) { return x - 3; }, -5, 5, 0.5);

        test_expression("x * 2", [](float x) { return x * 2; }, -3, 3, 0.3);

        test_expression("x / 4", [](float x) { return x / 4; }, -8, 8, 0.8);

        test_expression("x ^ 2", [](float x) { return x * x; }, -4, 4, 0.4);
    }

    BOOST_AUTO_TEST_CASE(math_functions) {
        test_expression("sin(x)", [](float x) { return std::sin(x); }, -3.14f, 3.14f, 0.1f);
        test_expression("cos(x)", [](float x) { return std::cos(x); }, -3.14f, 3.14f, 0.1f);

        test_expression("log(x)", [](float x) { return std::log(x); }, 0.1f, 10, 0.5f);
        test_expression("exp(x)", [](float x) { return std::exp(x); }, -2, 2, 0.2f);

        test_expression("sqrt(x)", [](float x) { return std::sqrt(x); }, 0, 10, 0.5f);
    }

    BOOST_AUTO_TEST_CASE(special_cases) {
        Expression expr = Expression(ExpressionParser::parse("1/x").value());
        BOOST_TEST(!expr.evaluate(0).has_value());

        expr = ExpressionParser::parse("log(x)").value();
        BOOST_TEST(!expr.evaluate(-1).has_value());

        expr = ExpressionParser::parse("sqrt(x)").value();
        BOOST_TEST(!expr.evaluate(-1).has_value());
    }

    BOOST_AUTO_TEST_CASE(constant_expression) {
        Expression expr = Expression(ExpressionParser::parse("2 + 3*5").value());
        auto res = expr.evaluate(0);
        BOOST_TEST(res.has_value());
        BOOST_TEST(res.value() == 17);

        expr = ExpressionParser::parse("pi + 1").value();
        res = expr.evaluate(0);
        BOOST_TEST(res.has_value());
        BOOST_CHECK_CLOSE(res.value(), Constants::PI + 1, GameConstants::EPS);
    }

    BOOST_AUTO_TEST_CASE(combined_expressions) {
        test_expression("(x + 1)*(x - 1)", [](float x) { return (x + 1) * (x - 1); }, -3, 3, 0.3);
        test_expression("x^2 + 2*x + 1", [](float x) { return x * x + 2 * x + 1; }, -5, 5, 0.5);
        test_expression("(x + 5)/(x - 2)", [](float x) { return (x + 5) / (x - 2); }, -4, 4, 0.8);
        test_expression("e^(-x^2) * sin(x) + x * cos(x)",
                        [](float x) { return std::exp(-x * x) * std::sin(x) + x * std::cos(x); }, -5, 5, 0.1);
    }


BOOST_AUTO_TEST_SUITE_END()
