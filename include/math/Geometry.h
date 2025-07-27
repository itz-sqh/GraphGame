#pragma once
#include <SFML/System/Vector2.hpp>
#include<cmath>
#include<vector>
#include "objects/CircleObject.h"
#include "core/GameConstants.h"
#include<SFML/Graphics/VertexArray.hpp>


namespace Geometry {
    struct Line { //ax+by+c=0;
        float a, b, c;

        Line(sf::Vector2f p1, sf::Vector2f p2);
        Line(float a, float b, float c);

        [[nodiscard]] static bool equals(const Line& l1, const Line &l2);

    };
    sf::Vector2f mapToWindow(sf::Vector2f pos, sf::Vector2u size, float minX = GameConstants::MIN_X, float maxX = GameConstants::MAX_X, float minY = GameConstants::MIN_Y, float maxY = GameConstants::MAX_Y);
    float mapToWindow(float value, unsigned sizeX, float minX = GameConstants::MIN_X, float maxX = GameConstants::MAX_X);
    float dist(sf::Vector2f p1, sf::Vector2f p2 = {0, 0});
    float distSq(sf::Vector2f p1, sf::Vector2f p2 = {0, 0});
    float distToSegment(sf::Vector2f p1, sf::Vector2f seg1, sf::Vector2f seg2);
    std::vector<sf::Vector2f> circleLineIntersection(const CircleObject& circle, Line line);
    std::vector<sf::Vector2f> circleIntersection(const CircleObject& circle1, const CircleObject& circle2);
    int findCenterIndex(const sf::VertexArray& vertices, sf::Vector2f position);


}
