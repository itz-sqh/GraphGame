#include "CircleObject.h"

#include "Player.h"


CircleObject::CircleObject(sf::Vector2f position, float radius) : position(position), radius(radius) {}


bool CircleObject::operator==(const CircleObject &other) const {
    return abs(this->getX() - other.getX()) < GameConstants::EPS &&
           abs(this->getY() - other.getY()) < GameConstants::EPS &&
           abs(this->getRadius() - other.getRadius()) < GameConstants::EPS;
}

bool CircleObject::operator!=(const CircleObject &other) const {
    return !(*this == other);
}

float CircleObject::getX() const { return position.x; }

float CircleObject::getY() const { return position.y; }

float CircleObject::getRadius() const { return radius; }

sf::Vector2f CircleObject::getPosition() const { return position; }

bool CircleObject::inside(sf::Vector2f point) {
    return Geometry::distSq(point, position) - radius * radius <= 0;
}

