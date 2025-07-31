#include "objects/CircleObject.h"


CircleObject::CircleObject(sf::Vector2f position, float radius) : position(position), radius(radius) {
}


bool CircleObject::operator==(const CircleObject &other) const {
    return std::abs(this->getX() - other.getX()) < GameConstants::EPS &&
           std::abs(this->getY() - other.getY()) < GameConstants::EPS &&
           std::abs(this->getRadius() - other.getRadius()) < GameConstants::EPS;
}

bool CircleObject::operator!=(const CircleObject &other) const {
    return !(*this == other);
}

float CircleObject::getX() const { return position.x; }

float CircleObject::getY() const { return position.y; }

float CircleObject::getRadius() const { return radius; }

sf::Vector2f CircleObject::getPosition() const { return position; }

bool CircleObject::inside(const sf::Vector2f point) const {
    const float x = point.x - position.x;
    const float y = point.y - position.y;
    return x * x + y * y - radius * radius < +GameConstants::EPS;
}

std::ostream& operator<<(std::ostream& os, const CircleObject& obj) {
    os << "CircleObject{x: " << obj.position.x
       << ", y: " << obj.position.y
       << ", r: " << obj.radius << "}";
    return os;
}
