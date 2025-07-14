#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f position, float radius) : CircleObject(position, radius) {}

void Obstacle::draw(sf::RenderTarget &target) const {
    sf::Vector2u size = target.getSize();
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(mapToWindow(position,size));
    shape.setOrigin({radius, radius});
    target.draw(shape);
}




