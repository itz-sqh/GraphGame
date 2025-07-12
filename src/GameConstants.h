#pragma once

#include<cmath>

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
    constexpr float HIT_RADIUS = 0.5f;
    constexpr float SHOT_DISPLAY_TIME = 5.0f;
    constexpr float PLAYER_RADIUS = 5.0f;
    constexpr float OBSTACLE_RADIUS = 30.0f;
    constexpr float DISTANCE_BETWEEN_PLAYERS = PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE = OBSTACLE_RADIUS + PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_OBSTACLES = OBSTACLE_RADIUS;
    constexpr sf::Color PLAYER_COLOR[] = {sf::Color::Red, sf::Color::Blue};

}

static sf::Vector2f mapToWindow(sf::Vector2f pos,
                                sf::Vector2u size) {
    float x = (pos.x - GameConstants::MIN_X) / (GameConstants::MAX_X - GameConstants::MIN_X);
    float y = (pos.y - GameConstants::MIN_Y) / (GameConstants::MAX_Y - GameConstants::MIN_Y);

    return {
            x * size.x,
            size.y - y * size.y
    };
}

static float dist(const sf::Vector2f p1, const sf::Vector2f p2 = {0, 0}) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

static float distSq(const sf::Vector2f p1, const sf::Vector2f p2 = {0, 0}) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}