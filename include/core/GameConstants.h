#pragma once
#include<SFML/Graphics.hpp>

namespace GameConstants {
    // x y must be in the same proportion as (width,height)
    constexpr float MAX_X = 25.f;
    constexpr float MIN_X = -25.f;
    constexpr float MAX_Y = 18.75f;
    constexpr float MIN_Y = -18.75f;

    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;

    constexpr float POINT_STEP = 0.025f;

    constexpr int PLAYER_COUNT = 2;
    constexpr int UNITS_PER_PLAYER = 2;
    constexpr int OBSTACLE_COUNT = 20;

    constexpr float EPS = 1e-3f;

    constexpr float SHOT_DISPLAY_TIME = 5.0f;
    constexpr int POINTS_PER_SECOND = 1000;

    constexpr float HIT_RADIUS = 0.75f;
    constexpr float PLAYER_RADIUS = 0.33f;
    constexpr float OBSTACLE_RADIUS = 2.f;

    constexpr float DISTANCE_BETWEEN_PLAYERS = PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE = OBSTACLE_RADIUS + PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_OBSTACLES = OBSTACLE_RADIUS;

    constexpr sf::Color PLAYER_COLOR[] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};

    constexpr unsigned int MAX_INPUT_SIZE = 50;

    constexpr float PLAYER_WIDTH_OFFSET = 20.f;
    constexpr float PLAYER_HEIGHT_OFFSET = 50.f;


    constexpr float BOT_THINK_TIME = 1.f;
    constexpr float BOT_TYPING_DELAY = 0.2f;
    constexpr float BOT_POST_TYPING_DELAY = 1.f;
}




