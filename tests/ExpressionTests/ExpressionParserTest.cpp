#define BOOST_TEST_MODULE ExpressionParserTest
#include<boost/test/unit_test.hpp>
#include "expression/ExpressionParser.h"
#include"expression/ExpressionTokenizer.h"


BOOST_AUTO_TEST_SUITE(ExpressionParserTest)

    BOOST_AUTO_TEST_CASE(tokenizer_test) { {
            auto tokens = ExpressionTokenizer::tokenize("3 + 4.25");
            BOOST_TEST(tokens.has_value());
            auto observed = tokens.value();

            std::vector<Token> expected = {
                {TokenType::Constant, "3"},
                {TokenType::BinaryOperator, "+"},
                {TokenType::Constant, "4.25"}
            };
            BOOST_CHECK_EQUAL(observed.size(), expected.size());
            BOOST_TEST(std::equal(observed.begin(), observed.end(), expected.begin()));
        } {
            auto tokens = ExpressionTokenizer::tokenize("X + sin(X)");
            BOOST_TEST(tokens.has_value());
            auto observed = tokens.value();
            std::vector<Token> expected = {
                {TokenType::Variable, "x"},
                {TokenType::BinaryOperator, "+"},
                {TokenType::Function, "sin"},
                {TokenType::LeftParen, "("},
                {TokenType::Variable, "x"},
                {TokenType::RightParen, ")"}
            };
            BOOST_CHECK_EQUAL(observed.size(), expected.size());
            BOOST_TEST(std::equal(observed.begin(), observed.end(), expected.begin()));
        } {
            auto tokens = ExpressionTokenizer::tokenize("pi + e");
            BOOST_TEST(tokens.has_value());
            auto observed = tokens.value();
            std::vector<Token> expected = {
                {TokenType::Constant, std::to_string(ExprOps::PI)},
                {TokenType::BinaryOperator, "+"},
                {TokenType::Constant, std::to_string(ExprOps::E)}
            };
            BOOST_CHECK_EQUAL(observed.size(), expected.size());
            BOOST_TEST(std::equal(observed.begin(), observed.end(), expected.begin()));
        } {
            auto tokens = ExpressionTokenizer::tokenize("-3 + +X");
            BOOST_TEST(tokens.has_value());
            auto observed = tokens.value();
            std::vector<Token> expected = {
                {TokenType::UnaryOperator, "u-"},
                {TokenType::Constant, "3"},
                {TokenType::BinaryOperator, "+"},
                {TokenType::UnaryOperator, "u+"},
                {TokenType::Variable, "x"}
            };
            BOOST_CHECK_EQUAL(observed.size(), expected.size());
            BOOST_TEST(std::equal(observed.begin(), observed.end(), expected.begin()));
        } {
            auto tokens = ExpressionTokenizer::tokenize("((x) + (2))*(3)");
            BOOST_TEST(tokens.has_value());
            auto observed = tokens.value();
            std::vector<Token> expected = {
                {TokenType::LeftParen, "("},
                {TokenType::LeftParen, "("},
                {TokenType::Variable, "x"},
                {TokenType::RightParen, ")"},
                {TokenType::BinaryOperator, "+"},
                {TokenType::LeftParen, "("},
                {TokenType::Constant, "2"},
                {TokenType::RightParen, ")"},
                {TokenType::RightParen, ")"},
                {TokenType::BinaryOperator, "*"},
                {TokenType::LeftParen, "("},
                {TokenType::Constant, "3"},
                {TokenType::RightParen, ")"}
            };
            BOOST_CHECK_EQUAL(observed.size(), expected.size());
            BOOST_TEST(std::equal(observed.begin(), observed.end(), expected.begin()));
        }
    }

    BOOST_AUTO_TEST_CASE(parser_test) {
        // No variable test
        {
            auto observed = ExpressionParser::parse("3 + 4 * 2 / (1 - 5) ^ 2 ^ 3");


            std::vector<Token> tokens = {
                {TokenType::Constant, "3"},
                {TokenType::Constant, "4"},
                {TokenType::Constant, "2"},
                {TokenType::BinaryOperator, "*"},
                {TokenType::Constant, "1"},
                {TokenType::Constant, "5"},
                {TokenType::BinaryOperator, "-"},
                {TokenType::Constant, "2"},
                {TokenType::Constant, "3"},
                {TokenType::BinaryOperator, "^"},
                {TokenType::BinaryOperator, "^"},
                {TokenType::BinaryOperator, "/"},
                {TokenType::BinaryOperator, "+"}
            };

            Expression expected;
            for (auto &&token: tokens) {
                expected.add(token);
            }

            BOOST_CHECK(Expression::isEqual(observed.value(),expected));
        }

        // No variable test
        {
            auto observed = ExpressionParser::parse("sin(max(2, 3) / 3 * pi)");

            std::vector<Token> tokens = {
                {TokenType::Constant, "2"},
                {TokenType::Constant, "3"},
                {TokenType::Function, "max"},
                {TokenType::Constant, "3"},
                {TokenType::BinaryOperator, "/"},
                {TokenType::Constant, std::to_string(ExprOps::PI)},
                {TokenType::BinaryOperator, "*"},
                {TokenType::Function, "sin"}
            };

            Expression expected;
            for (auto &&token: tokens) {
                expected.add(token);
            }

            BOOST_CHECK(Expression::isEqual(observed.value(),expected));
        }
        // Test with x variable
        {
            auto observed = ExpressionParser::parse("3 + 4 * x / x");

            std::vector<Token> tokens = {
                {TokenType::Constant, "3"},
                {TokenType::Constant, "4"},
                {TokenType::Variable, "x"},
                {TokenType::BinaryOperator, "*"},
                {TokenType::Variable, "x"},
                {TokenType::BinaryOperator, "/"},
                {TokenType::BinaryOperator, "+"}
            };

            Expression expected;
            for (auto &&token: tokens) {
                expected.add(token);
            }


            BOOST_CHECK(Expression::isEqual(observed.value(),expected));
        }

        // Test with x variable
        {
            auto observed = ExpressionParser::parse("sin(max(2, x) / x * X)");

            std::vector<Token> tokens = {
                {TokenType::Constant, "2"},
                {TokenType::Variable, "x"},
                {TokenType::Function, "max"},
                {TokenType::Variable, "x"},
                {TokenType::BinaryOperator, "/"},
                {TokenType::Variable, "x"},
                {TokenType::BinaryOperator, "*"},
                {TokenType::Function, "sin"}
            };

            Expression expected;
            for (auto &&token: tokens) {
                expected.add(token);
            }


            BOOST_CHECK(Expression::isEqual(observed.value(),expected));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
