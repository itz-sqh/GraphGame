#pragma once
#include <SFML/Graphics.hpp>
#include "math/Geometry.h"
#include "CircleObject.h"
#include "core/GameConstants.h"

class Obstacle : public CircleObject {
public:
    explicit Obstacle(sf::Vector2f position, float radius = GameConstants::OBSTACLE_RADIUS);

    void draw(sf::RenderTarget &target) const;

    std::vector<CircleObject> getOverlaps();

    void addOverlap(sf::Vector2f position);

    [[nodiscard]] bool isOverlapped(sf::Vector2f point, const CircleObject &without = CircleObject({0, 0}, 0)) const;

    ~Obstacle() override = default;

private:
    std::vector<CircleObject> overlaps;
};
