#pragma once
#include "ExpressionParser/Expression.h"
#include <SFML/Graphics.hpp>
#include"GameConstants.h"

class Player {
public:
    Player(sf::Vector2f position, sf::Color color, float radius = GameConstants::PLAYER_RADIUS);

    void draw(sf::RenderTarget& target) const;

    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] sf::Vector2f getPosition() const;
    [[nodiscard]] float getRadius() const;
    [[nodiscard]] sf::Color getColor() const;

private:
    sf::Vector2f position;
    bool gotHit;
    float radius;
    sf::Color color;
};