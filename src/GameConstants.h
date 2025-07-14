#pragma once

#include<cmath>

#include"CircleObject.h"
#include<vector>
namespace GameConstants {
    constexpr float MAX_X = 25;
    constexpr float MIN_X = -25;
    constexpr float MAX_Y = 15;
    constexpr float MIN_Y = -15;
    constexpr float POINTS_STEP = 0.025;
    constexpr int PLAYER_COUNT = 2;
    constexpr int OBSTACLE_COUNT = 10;
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;
    constexpr float EPS = 1e-3;
    constexpr float HIT_RADIUS = 0.5f;
    constexpr float SHOT_DISPLAY_TIME = 5.0f;
    constexpr float PLAYER_RADIUS = 5.0f;
    constexpr float OBSTACLE_RADIUS = 30.0f;
    constexpr float DISTANCE_BETWEEN_PLAYERS = PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE = OBSTACLE_RADIUS + PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_OBSTACLES = OBSTACLE_RADIUS;
    constexpr sf::Color PLAYER_COLOR[] = {sf::Color::Red, sf::Color::Blue};
    constexpr unsigned int MAX_INPUT_SIZE = 50;
    constexpr float PLAYER_WIDTH_OFFSET = 20;
    constexpr float PLAYER_HEIGHT_OFFSET = 50;
}
struct Line {//ax+by+c=0;
    float a, b, c;

    Line(const sf::Vector2f p1, const sf::Vector2f p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -p1.x * a - p1.y * b;
        const float m = std::sqrt(a * a + b * b);
        a /= m;
        b /= m;
        c /= m;
    }
    Line(const float a, const float b, const float c) : a(a), b(b), c(c) {
        const float m = std::sqrt(a * a + b * b);
        this->a /= m;
        this->b /= m;
        this->c /= m;
    }
};

static sf::Vector2f mapToWindow(const sf::Vector2f pos,
                                const sf::Vector2u size) {
    float x = (pos.x - GameConstants::MIN_X) / (GameConstants::MAX_X - GameConstants::MIN_X);
    float y = (pos.y - GameConstants::MIN_Y) / (GameConstants::MAX_Y - GameConstants::MIN_Y);

    return {
            x * static_cast<float>(size.x),
            static_cast<float>(size.y) - y * static_cast<float>(size.y)
    };
}

static float dist(const sf::Vector2f p1, const sf::Vector2f p2 = {0, 0}) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

static float distSq(const sf::Vector2f p1, const sf::Vector2f p2 = {0, 0}) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

static std::vector<sf::Vector2f> circleLineIntersection(const CircleObject& circle,Line line) {
    const float r = circle.getRadius();
    const sf::Vector2f offset = circle.getPosition();

    line.c += line.a * offset.x + line.b * offset.y;

    float x0 = -line.a*line.c;
    float y0 = -line.b*line.c;
    if (line.c*line.c > r*r + GameConstants::EPS) {
        return {};
    }
    if (abs(line.c*line.c - r*r) < GameConstants::EPS) {
        return {{x0,y0}};
    }
    float d = r*r-line.c*line.c;
    float mult = std::sqrt(d);
    float ax,ay,bx,by;
    ax = x0 + line.b*mult;
    bx = x0 - line.b*mult;
    ay = y0 - line.a*mult;
    by = y0 + line.a*mult;
    return {{ax+offset.x,ay+offset.y},{bx+offset.x,by+offset.y}};
}
static std::vector<sf::Vector2f> circleIntersection(const CircleObject& circle1, const CircleObject& circle2) {
    //TODO check case when circle centers at the same point
    const sf::Vector2f offset1 = circle1.getPosition();
    const float r1 = circle1.getRadius();
    const sf::Vector2f offset2 = circle2.getPosition();
    const float r2 = circle2.getRadius();
    //a(x-offset1.x) + b(y-offset1.y) + c
    //a*x+b*y - a*offset1.x - b*offset1.y + c
    const sf::Vector2f d = offset2 - offset1;

    const float a = -2 * d.x;
    const float b = -2 * d.y;
    const float c = d.x*d.x+d.y*d.y+r1*r1-r2*r2 - a*offset1.x - b*offset1.y;


    Line line(a,b,c);

    return circleLineIntersection(circle2,line);

}

