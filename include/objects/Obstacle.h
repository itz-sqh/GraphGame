#pragma once
#include <SFML/Graphics.hpp>
#include "math/Geometry.h"
#include "CircleObject.h"
#include "core/GameConstants.h"

class Obstacle : public CircleObject {
public:
    explicit Obstacle(sf::Vector2f position, float radius = GameConstants::OBSTACLE_RADIUS);

    Obstacle() = default;

    ~Obstacle() override = default;

    void draw(sf::RenderTarget &target) const;

    [[nodiscard]] bool isOverlapped(sf::Vector2f point, const CircleObject &without = CircleObject()) const;

    void addOverlap(sf::Vector2f position);

    std::vector<CircleObject> getOverlaps();

private:
    std::vector<CircleObject> overlaps;
};
