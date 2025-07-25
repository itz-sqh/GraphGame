#define BOOST_TEST_MODULE DistanceTest
#include<boost/test/unit_test.hpp>
#include"Geometry.h"


BOOST_AUTO_TEST_SUITE(DistanceTest)

    constexpr float eps = GameConstants::EPS;


    // dist between (3,4) and (0,0)
    BOOST_AUTO_TEST_CASE(distane_between_points) {
        {
            sf::Vector2f p1(3.f, 4.f);

            float observed = Geometry::dist(p1);
            float expected = 5.f;

            BOOST_CHECK_CLOSE(observed, expected, eps);
        }
        // dist between (3,4) and (10,0)
        {
            sf::Vector2f p1(3.f,4.f);
            sf::Vector2f p2(10.f,0.f);

            float observed = Geometry::dist(p1,p2);
            float expected = std::sqrt(65.f);

            BOOST_CHECK_CLOSE(observed, expected, eps);

        }
        // dist between (1,1) and (2,2)
        {
            sf::Vector2f p1(1.f,1.f);
            sf::Vector2f p2(2.f,2.f);

            float observed = Geometry::dist(p1,p2);
            float expected = std::sqrt(2.f);

            BOOST_CHECK_CLOSE(observed, expected, eps);
        }

    }
    BOOST_AUTO_TEST_CASE(distance_between_points_squared) {
        {
            sf::Vector2f p1(3.f, 4.f);

            float observed = Geometry::distSq(p1);
            float expected = 25.f;

            BOOST_CHECK_CLOSE(observed, expected, eps);
        }
        // dist between (3,4) and (10,0)
        {
            sf::Vector2f p1(3.f,4.f);
            sf::Vector2f p2(10.f,0.f);

            float observed = Geometry::distSq(p1,p2);
            float expected = 65.f;

            BOOST_CHECK_CLOSE(observed, expected, eps);

        }
        // dist between (1,1) and (2,2)
        {
            sf::Vector2f p1(1.f,1.f);
            sf::Vector2f p2(2.f,2.f);

            float observed = Geometry::distSq(p1,p2);
            float expected = 2.f;

            BOOST_CHECK_CLOSE(observed, expected, eps);
        }
    }

    BOOST_AUTO_TEST_CASE(distane_between_point_and_segment) {

        //proj > 1.f
        {
            sf::Vector2f p(2.f,3.f);

            sf::Vector2f seg1(3.f, 4.f);
            sf::Vector2f seg2(10.f,0.f);

            float observed = Geometry::distToSegment(p,seg1,seg2);

            float expected = std::sqrt(2.f);

            BOOST_CHECK_CLOSE(observed, expected, eps);

        }


        {
            sf::Vector2f p(9.f,0.f);

            sf::Vector2f seg1(3.f, 4.f);
            sf::Vector2f seg2(10.f,0.f);

            float observed = Geometry::distToSegment(p,seg1,seg2);

            float expected = 0.496139f;

            BOOST_CHECK_CLOSE(observed, expected, eps);

        }

        {
            sf::Vector2f p(5.f,2.f);

            sf::Vector2f seg1(3.f, 4.f);
            sf::Vector2f seg2(10.f,0.f);

            float observed = Geometry::distToSegment(p,seg1,seg2);

            float expected = 0.744208f;

            BOOST_CHECK_CLOSE(observed, expected, eps);

        }

    }

BOOST_AUTO_TEST_SUITE_END()
