#pragma once
#include "ExpressionParser/Expression.h"
#include <SFML/Graphics.hpp>
#include"GameConstants.h"

class Player {
public:
    Player(sf::Vector2f position, sf::Color color, float radius = GameConstants::PLAYER_RADIUS);

    void draw(sf::RenderTarget& target) const;

    bool isAlive() const;
    float getX() const;
    float getY() const;
    sf::Vector2f getPosition() const;
    float getRadius() const;
    sf::Color getColor() const;

private:
    sf::Vector2f position;
    bool gotHit;
    float radius;
    sf::Color color;
};