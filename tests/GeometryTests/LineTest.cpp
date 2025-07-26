#define BOOST_TEST_MODULE LineTest
#include<boost/test/unit_test.hpp>
#include "../../include/math/Geometry.h"


BOOST_AUTO_TEST_SUITE(LineTest)


    BOOST_AUTO_TEST_CASE(constructor_from_coefficients_test) {
        // Test horizontal line (y - 3 = 0)
        {
            constexpr float a = 0.f;
            constexpr float b = -3.f;
            constexpr float c = 9.f;

            const Geometry::Line observed(a, b, c);

            constexpr float expected_a = 0;
            constexpr float expected_b = 1;
            constexpr float expected_c = -3;
            const Geometry::Line expected(expected_a, expected_b, expected_c);

            BOOST_CHECK(Geometry::Line::equals(observed, expected));
        }


        // Test diagonal line (x - y + 1 = 0)
        {
            constexpr float a = 2.f;
            constexpr float b = -2.f;
            constexpr float c = 2.f;

            const Geometry::Line observed(a, b, c);

            constexpr float expected_a = 1.0f / std::sqrt(2.0f);
            constexpr float expected_b = -1.0f / std::sqrt(2.0f);
            constexpr float expected_c = 1.0f / std::sqrt(2.0f);
            const Geometry::Line expected(expected_a, expected_b, expected_c);

            BOOST_CHECK(Geometry::Line::equals(observed, expected));
        }

        // Test another diagonal line (3x + 4y + 5 = 0)
        {
            constexpr float a = -6.f;
            constexpr float b = -8.f;
            constexpr float c = -10.f;

            const Geometry::Line observed(a, b, c);

            constexpr float expected_a = 0.6f;
            constexpr float expected_b = 0.8f;
            constexpr float expected_c = 1.f;
            const Geometry::Line expected(expected_a, expected_b, expected_c);

            BOOST_CHECK(Geometry::Line::equals(observed, expected));
        }
    }

    BOOST_AUTO_TEST_CASE(constructor_from_two_points_test) {
        // Test horizontal line (y - 3 = 0)
        {
            constexpr sf::Vector2f p1(0, 3);
            constexpr sf::Vector2f p2(3, 3);
            const Geometry::Line observed(p1, p2);

            constexpr float expected_a = 0.f;
            constexpr float expected_b = 1.f;
            constexpr float expected_c = -3.f;
            const Geometry::Line expected(expected_a, expected_b, expected_c);

            BOOST_CHECK(Geometry::Line::equals(observed, expected));
        }


        // Test diagonal line (x - y + 1 = 0)
        {
            constexpr sf::Vector2f p1(1, 2);
            constexpr sf::Vector2f p2(3, 4);

            const Geometry::Line observed(p1, p2);

            constexpr float expected_a = 1.0f / std::sqrt(2.0f);
            constexpr float expected_b = -1.0f / std::sqrt(2.0f);
            constexpr float expected_c = 1.0f / std::sqrt(2.0f);
            const Geometry::Line expected(expected_a, expected_b, expected_c);

            BOOST_CHECK(Geometry::Line::equals(observed, expected));
        }

        // Test another diagonal line (3x + 4y + 5 = 0)
        {
            constexpr sf::Vector2f p1(5.f, -5.f);
            constexpr sf::Vector2f p2(-1.f, -0.5f);

            const Geometry::Line observed(p1, p2);

            constexpr float expected_a = 0.6f;
            constexpr float expected_b = 0.8f;
            constexpr float expected_c = 1.f;
            const Geometry::Line expected(expected_a, expected_b, expected_c);

            BOOST_CHECK(Geometry::Line::equals(observed, expected));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
