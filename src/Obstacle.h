#pragma once
#include <SFML/Graphics.hpp>

#include "CircleObject.h"
#include"GameConstants.h"

class Obstacle : public CircleObject {
public:
    explicit Obstacle(sf::Vector2f position, float radius = GameConstants::OBSTACLE_RADIUS);

    void draw(sf::RenderTarget& target) const override;

    ~Obstacle() override = default;


private:
    std::vector<sf::Vector2f> overlaps;
};