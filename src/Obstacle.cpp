
#include "Obstacle.h"

#include "Geometry.h"

Obstacle::Obstacle(sf::Vector2f position, float radius) : CircleObject(position, radius) {}

void Obstacle::draw(sf::RenderTarget &target) const {
    sf::Vector2u size = target.getSize();
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(Geometry::mapToWindow(position,size));
    shape.setOrigin({radius, radius});
    target.draw(shape);

    sf::CircleShape overlap(GameConstants::HIT_RADIUS);
    overlap.setFillColor(sf::Color::White);
    overlap.setOrigin({GameConstants::HIT_RADIUS, GameConstants::HIT_RADIUS});
    for (const auto &x : overlaps) {
        overlap.setPosition(Geometry::mapToWindow(x,size));
        target.draw(overlap);
    }
}




