#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f position, float radius) : position(position), radius(radius) {}

void Obstacle::draw(sf::RenderTarget &target) const {
    sf::Vector2u size = target.getSize();
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(mapToWindow(position,size));
    target.draw(shape);
}


float Obstacle::getX() const { return position.x; }
float Obstacle::getY() const { return position.y; }
float Obstacle::getRadius() const { return radius; }
sf::Vector2f Obstacle::getPosition() const {return position;}

