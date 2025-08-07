#pragma once
#include<SFML/Graphics/Color.hpp>

namespace GameConstants {
    constexpr float MAX_X = 50.f/2.f;
    constexpr float MIN_X = -50.f/2.f;
    constexpr float MAX_Y = 28.125f/2.f;
    constexpr float MIN_Y = -28.125f/2.f;

    inline unsigned int WIDTH = 960;
    inline unsigned int HEIGHT = 540;

    constexpr float POINT_STEP = 0.025f;

    constexpr int PLAYER_COUNT = 2;
    constexpr int UNITS_PER_PLAYER = 2;
    constexpr int OBSTACLE_COUNT = 15;

    constexpr float EPS = 1e-3f;

    constexpr float SHOT_DISPLAY_TIME = 5.0f;
    constexpr int POINTS_PER_SECOND = 1000;

    constexpr float HIT_RADIUS = 0.5f;
    constexpr float PLAYER_RADIUS = 0.33f;
    constexpr float OBSTACLE_RADIUS = 2.f;

    constexpr float DISTANCE_BETWEEN_PLAYERS = PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE = OBSTACLE_RADIUS + PLAYER_RADIUS;
    constexpr float DISTANCE_BETWEEN_OBSTACLES = OBSTACLE_RADIUS;

    constexpr sf::Color PLAYER_COLOR[] = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Black};
    constexpr sf::Color BACKGROUND_COLOR = sf::Color(0x181818FF);

    constexpr unsigned int MAX_INPUT_SIZE = 50;

    constexpr float PLAYER_WIDTH_OFFSET = PLAYER_RADIUS;
    constexpr float PLAYER_HEIGHT_OFFSET = PLAYER_RADIUS;


    constexpr float BOT_THINK_TIME = 1.f;
    constexpr float BOT_TYPING_DELAY = 0.2f;
    constexpr float BOT_POST_TYPING_DELAY = 1.f;
}
