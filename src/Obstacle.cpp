
#include "Obstacle.h"



Obstacle::Obstacle(sf::Vector2f position, float radius) : CircleObject(position, radius) {}

void Obstacle::draw(sf::RenderTarget &target) const {
    sf::Vector2u size = target.getSize();
    float windowRadius = Geometry::scaleToWindow(radius,size);
    sf::CircleShape shape(windowRadius);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(Geometry::mapToWindow(position,size));
    shape.setOrigin({windowRadius, windowRadius});
    target.draw(shape);

    windowRadius = Geometry::scaleToWindow(GameConstants::HIT_RADIUS,size);
    sf::CircleShape overlap(windowRadius);
    overlap.setFillColor(sf::Color::White);
    overlap.setOrigin({windowRadius, windowRadius});
    for (const auto &x : overlaps) {
        overlap.setPosition(Geometry::mapToWindow(x,size));
        target.draw(overlap);
    }
}

void Obstacle::addOverlap(sf::Vector2f position) {
    overlaps.emplace_back(position);
}





