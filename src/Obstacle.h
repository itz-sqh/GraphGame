#pragma once
#include <SFML/Graphics.hpp>
#include"GameConstants.h"

class Obstacle {
public:
    Obstacle(sf::Vector2f position, float radius = GameConstants::OBSTACLE_RADIUS);

    void draw(sf::RenderTarget& target) const;

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getRadius() const;
    [[nodiscard]] sf::Vector2f getPosition() const;

private:
    sf::Vector2f position;
    std::vector<sf::Vector2f> overlaps;
    float radius;
};