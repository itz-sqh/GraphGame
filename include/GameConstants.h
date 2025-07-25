#pragma once

namespace GameConstants {
    constexpr float MAX_X = 25;
    constexpr float MIN_X = -25;
    constexpr float MAX_Y = 18.75;
    constexpr float MIN_Y = -18.75;

    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;

    constexpr float POINT_STEP = 0.025;

    constexpr int PLAYER_COUNT = 2;
    constexpr int OBSTACLE_COUNT = 10;

    constexpr float EPS = 1e-3;

    constexpr float SHOT_DISPLAY_TIME = 5.0f;
    constexpr float TIME_TO_PLOT = 3.0f;

    constexpr float HIT_RADIUS = 0.5f;
    constexpr float PLAYER_RADIUS = 0.33f;
    constexpr float OBSTACLE_RADIUS = 2.f;

    constexpr float DISTANCE_BETWEEN_PLAYERS = PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE = OBSTACLE_RADIUS + PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_OBSTACLES = OBSTACLE_RADIUS;

    constexpr sf::Color PLAYER_COLOR[] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};

    constexpr unsigned int MAX_INPUT_SIZE = 50;

    constexpr float PLAYER_WIDTH_OFFSET = 20;
    constexpr float PLAYER_HEIGHT_OFFSET = 50;
}




