#define BOOST_TEST_MODULE CoordinateSystemTest
#include<boost/test/unit_test.hpp>
#include"Geometry.h"
#include<SFML/System/Vector2.hpp>


const std::vector<sf::Vector2u> windowSizes = {
    {800, 600},
    {1920, 1080},
    {1024, 768},
    {2560, 1440},
    {1280, 720}
};
constexpr float eps = GameConstants::EPS;

const std::vector<std::tuple<float, float, float, float> > coordinateRanges = {
    {GameConstants::MIN_X, GameConstants::MAX_X, GameConstants::MIN_Y, GameConstants::MAX_Y},
    {-10.f, 10.f, -10.f, 10.f},
    {0.f, 100.f, 0.f, 100.f},
    {-50.f, 55.f, -25.f, 20.f},
    {-1.f, 1.f, -1.f, 1.f},
    {-2.f, -1.f, 0.f, 1.f}
};


void test_point_mapping(sf::Vector2f pos, sf::Vector2u windowSize, sf::Vector2f expected, float minX, float maxX,
                        float minY, float maxY) {
    auto observed = Geometry::mapToWindow(pos, windowSize, minX, maxX, minY, maxY);

    BOOST_CHECK_CLOSE(observed.x, expected.x, eps);
    BOOST_CHECK_CLOSE(observed.y, expected.y, eps);
}

void test_scalar_mapping(float value, unsigned windowSize, float expected, float minX, float maxX) {
    auto observed = Geometry::mapToWindow(value, windowSize, minX, maxX);

    BOOST_CHECK_CLOSE(observed, expected, eps);
}


BOOST_AUTO_TEST_SUITE(CoordinateSystemTest)


    BOOST_AUTO_TEST_CASE(point_mapping_test) {
        for (const auto &windowSize: windowSizes) {
            for (const auto &range: coordinateRanges) {
                auto [minX, maxX, minY, maxY] = range;

                float cx = (minX + maxX) / 2.f;
                float cy = (minY + maxY) / 2.f;

                sf::Vector2f expectedCenter(static_cast<float>(windowSize.x) / 2.f,
                                            static_cast<float>(windowSize.y) / 2.f);
                test_point_mapping({cx, cy}, windowSize, expectedCenter, minX, maxX, minY, maxY);

                sf::Vector2f expectedMin(0.f, static_cast<float>(windowSize.y));
                test_point_mapping({minX, minY}, windowSize, expectedMin, minX, maxX, minY, maxY);

                sf::Vector2f expectedMax(static_cast<float>(windowSize.x), 0.f);
                test_point_mapping({maxX, maxY}, windowSize, expectedMax, minX, maxX, minY, maxY);
            }
        }
    }

    BOOST_AUTO_TEST_CASE(scalar_mapping_test) {
        for (const auto &windowSize: windowSizes) {
            for (const auto &range: coordinateRanges) {
                auto [minX, maxX, minY, maxY] = range;


                // minX from [minX, maxX] to [0, sizeX]
                test_scalar_mapping(minX, windowSize.x, 0.f, minX, maxX);
                // minY from [minY, maxY] to [0, sizeY]
                test_scalar_mapping(minY, windowSize.y, 0.f, minY, maxY);

                // maxX from [minX, maxX] to [0, sizeX]
                test_scalar_mapping(maxX, windowSize.x, static_cast<float>(windowSize.x), minX, maxX);
                // maxY from [minY, maxY] to [0, sizeY]
                test_scalar_mapping(maxY, windowSize.y, static_cast<float>(windowSize.y), minY, maxY);

                // (minX+maxX)/2 from [minX, maxX] to [0, sizeX]
                test_scalar_mapping((minX + maxX) / 2.f, windowSize.x,
                                    static_cast<float>(windowSize.x) / 2.f,
                                    minX, maxX);
                // (minY+maxY)/2 from [minY, maxY] to [0, sizeY]
                test_scalar_mapping((minY + maxY) / 2.f, windowSize.y,
                                    static_cast<float>(windowSize.y) / 2.f,
                                    minY, maxY);
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()
