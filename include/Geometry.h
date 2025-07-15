#pragma once
#include <SFML/System/Vector2.hpp>
#include<cmath>
#include<vector>
#include "CircleObject.h"
#include "GameConstants.h"

namespace Geometry {
    struct Line {//ax+by+c=0;
        float a, b, c;

        Line(const sf::Vector2f p1, const sf::Vector2f p2);
        Line(const float a, const float b, const float c);
    };
    sf::Vector2f mapToWindow(const sf::Vector2f pos, const sf::Vector2u size);
    float scaleToWindow(float value, const sf::Vector2u size);
    float dist(const sf::Vector2f p1, const sf::Vector2f p2 = {0, 0});
    float distSq(const sf::Vector2f p1, const sf::Vector2f p2 = {0, 0});
    std::vector<sf::Vector2f> circleLineIntersection(const CircleObject& circle, Line line);
    std::vector<sf::Vector2f> circleIntersection(const CircleObject& circle1, const CircleObject& circle2);

}
