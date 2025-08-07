#define BOOST_TEST_MODULE ExpressionValidationTest
#include <boost/test/unit_test.hpp>
#include "expression/ExpressionParser.h"

BOOST_AUTO_TEST_SUITE(ExpressionValidationTest)

    BOOST_AUTO_TEST_CASE(valid_expressions) {
        BOOST_TEST(ExpressionParser::parse("x + 5").has_value());
        BOOST_TEST(ExpressionParser::parse("3 * x - 2").has_value());
        BOOST_TEST(ExpressionParser::parse("(x + 1) * (x - 1)").has_value());
        BOOST_TEST(ExpressionParser::parse("x^2 + x^2").has_value());


        BOOST_TEST(ExpressionParser::parse("sin(x)").has_value());
        BOOST_TEST(ExpressionParser::parse("cos(x + 1)").has_value());
        BOOST_TEST(ExpressionParser::parse("sqrt(x) + log(x)").has_value());


        BOOST_TEST(ExpressionParser::parse("3.14").has_value());
        BOOST_TEST(ExpressionParser::parse("2 + 2 * 2").has_value());

        BOOST_TEST(ExpressionParser::parse("+x + -x").has_value());


        BOOST_TEST(ExpressionParser::parse("(sin(x)^2 + cos(x)^2) * log(10)").has_value());
    }

    BOOST_AUTO_TEST_CASE(invalid_expressions) {
        BOOST_TEST(!ExpressionParser::parse("").has_value());


        BOOST_TEST(!ExpressionParser::parse("(x + 1").has_value());
        BOOST_TEST(!ExpressionParser::parse("x + 1)").has_value());
        BOOST_TEST(!ExpressionParser::parse("sin(x").has_value());


        BOOST_TEST(!ExpressionParser::parse("x +").has_value());
        BOOST_TEST(!ExpressionParser::parse("* x").has_value());
        BOOST_TEST(!ExpressionParser::parse("x + * x").has_value());


        BOOST_TEST(!ExpressionParser::parse("foo(x)").has_value());
        BOOST_TEST(!ExpressionParser::parse("123(x)").has_value());


        BOOST_TEST(!ExpressionParser::parse("1..5").has_value());
        BOOST_TEST(!ExpressionParser::parse("12.34.56").has_value());
        BOOST_TEST(!ExpressionParser::parse("1.2e3.4").has_value());


        BOOST_TEST(!ExpressionParser::parse("x @ y").has_value());
        BOOST_TEST(!ExpressionParser::parse("x # 2").has_value());
    }

    BOOST_AUTO_TEST_CASE(special_cases) {
        BOOST_TEST(ExpressionParser::parse("x").has_value());


        BOOST_TEST(!ExpressionParser::parse("+").has_value());


        BOOST_TEST(!ExpressionParser::parse("x +++ y").has_value());


        BOOST_TEST(!ExpressionParser::parse("()").has_value());

        BOOST_TEST(!ExpressionParser::parse("sin(x,x)").has_value());


        BOOST_TEST(!ExpressionParser::parse("(,)").has_value());
    }

BOOST_AUTO_TEST_SUITE_END()
