#define BOOST_TEST_MODULE ExpressionValidationTest
#include <boost/test/unit_test.hpp>
#include "ExpressionParser.h"

BOOST_AUTO_TEST_SUITE(ExpressionValidationTest)

    BOOST_AUTO_TEST_CASE(valid_expressions) {
        BOOST_TEST(ExpressionParser::parse("x + 5").isValid());
        BOOST_TEST(ExpressionParser::parse("3 * x - 2").isValid());
        BOOST_TEST(ExpressionParser::parse("(x + 1) * (x - 1)").isValid());
        BOOST_TEST(ExpressionParser::parse("x^2 + x^2").isValid());


        BOOST_TEST(ExpressionParser::parse("sin(x)").isValid());
        BOOST_TEST(ExpressionParser::parse("cos(x + 1)").isValid());
        BOOST_TEST(ExpressionParser::parse("sqrt(x) + log(x)").isValid());


        BOOST_TEST(ExpressionParser::parse("3.14").isValid());
        BOOST_TEST(ExpressionParser::parse("2 + 2 * 2").isValid());

        BOOST_TEST(ExpressionParser::parse("+x + -x").isValid());


        BOOST_TEST(ExpressionParser::parse("(sin(x)^2 + cos(x)^2) * log(10)").isValid());
    }

    BOOST_AUTO_TEST_CASE(invalid_expressions) {
        BOOST_TEST(!ExpressionParser::parse("").isValid());


        BOOST_TEST(!ExpressionParser::parse("(x + 1").isValid());
        BOOST_TEST(!ExpressionParser::parse("x + 1)").isValid());
        BOOST_TEST(!ExpressionParser::parse("sin(x").isValid());


        BOOST_TEST(!ExpressionParser::parse("x +").isValid());
        BOOST_TEST(!ExpressionParser::parse("* x").isValid());
        BOOST_TEST(!ExpressionParser::parse("x + * x").isValid());


        BOOST_TEST(!ExpressionParser::parse("foo(x)").isValid());
        BOOST_TEST(!ExpressionParser::parse("123(x)").isValid());


        BOOST_TEST(!ExpressionParser::parse("1..5").isValid());
        BOOST_TEST(!ExpressionParser::parse("12.34.56").isValid());
        BOOST_TEST(!ExpressionParser::parse("1.2e3.4").isValid());


        BOOST_TEST(!ExpressionParser::parse("x @ y").isValid());
        BOOST_TEST(!ExpressionParser::parse("x # 2").isValid());
    }

    BOOST_AUTO_TEST_CASE(special_cases) {
        BOOST_TEST(ExpressionParser::parse("x").isValid());


        BOOST_TEST(!ExpressionParser::parse("+").isValid());


        BOOST_TEST(!ExpressionParser::parse("x +++ y").isValid());


        BOOST_TEST(!ExpressionParser::parse("()").isValid());


        BOOST_TEST(!ExpressionParser::parse("(,)").isValid());
    }

BOOST_AUTO_TEST_SUITE_END()
