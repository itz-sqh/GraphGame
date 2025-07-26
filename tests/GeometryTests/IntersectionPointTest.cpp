#define BOOST_TEST_MODULE IntersectionPointTest
#include<boost/test/unit_test.hpp>
#include"Geometry.h"


BOOST_AUTO_TEST_SUITE(IntersectionPointTest)

    constexpr float eps = GameConstants::EPS;

    BOOST_AUTO_TEST_CASE(circle_line_intersection_test) { {
            CircleObject circle({3.f, 4.f}, 5.f);
            Geometry::Line line(7.f, 8.f, 9.f);

            auto observed = circleLineIntersection(circle, line);

            BOOST_CHECK_EQUAL(observed.size(), 0);
        } {
            CircleObject circle({3.f, 4.f}, 5.f);
            Geometry::Line line(3.f, 4.f, 0.f);

            auto observed = circleLineIntersection(circle, line);

            BOOST_CHECK_EQUAL(observed.size(), 1);

            BOOST_CHECK_EQUAL(observed[0].x, 0.f);
            BOOST_CHECK_EQUAL(observed[0].y, 0.f);
        } {
            CircleObject circle({3.f, 4.f}, 5.f);
            Geometry::Line line(3.f, 4.f, -5.f);

            auto observed = circleLineIntersection(circle, line);

            BOOST_CHECK_EQUAL(observed.size(), 2);

            if (observed[0].x > observed[1].x) std::swap(observed[0], observed[1]);

            BOOST_CHECK_CLOSE(observed[0].x, -1.8f, eps);
            BOOST_CHECK_CLOSE(observed[0].y, 2.6f, eps);

            BOOST_CHECK_CLOSE(observed[1].x, 3.f, eps);
            BOOST_CHECK_CLOSE(observed[1].y, -1.f, eps);
        }
    }

    BOOST_AUTO_TEST_CASE(circle_intersection_test) { {
            CircleObject circle1({3.f, 4.f}, 5.f);
            CircleObject circle2({-3.f, -4.f}, 3.f);

            auto observed = Geometry::circleIntersection(circle1, circle2);

            BOOST_CHECK_EQUAL(observed.size(), 0);
        } {
            CircleObject circle({3.f, 4.f}, 5.f);
            CircleObject circle2({-3.f, -4.f}, 5.f);

            auto observed = Geometry::circleIntersection(circle, circle2);

            BOOST_CHECK_EQUAL(observed.size(), 1);

            BOOST_CHECK_CLOSE(observed[0].x, 0.f, eps);
            BOOST_CHECK_CLOSE(observed[0].y, 0.f, eps);
        } {
            CircleObject circle1({3.f, 4.f}, 5.f);
            CircleObject circle2({5.f, -1.f}, 3.f);

            auto observed = Geometry::circleIntersection(circle1, circle2);

            BOOST_CHECK_EQUAL(observed.size(), 2);

            if (observed[0].x > observed[1].x) std::swap(observed[0], observed[1]);

            BOOST_CHECK_CLOSE(observed[0].x, 2.00169f, eps);
            BOOST_CHECK_CLOSE(observed[0].y, -0.89932f, eps);

            BOOST_CHECK_CLOSE(observed[1].x, 7.10176f, eps);
            BOOST_CHECK_CLOSE(observed[1].y, 1.1407f, eps);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
