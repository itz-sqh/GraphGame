#include "objects/CircleObject.h"


CircleObject::CircleObject(sf::Vector2f position, float radius) : m_position(position), m_radius(radius) {}


bool CircleObject::operator==(const CircleObject &other) const {
    return std::abs(this->getX() - other.getX()) < GameConstants::EPS &&
           std::abs(this->getY() - other.getY()) < GameConstants::EPS &&
           std::abs(this->getRadius() - other.getRadius()) < GameConstants::EPS;
}

bool CircleObject::operator!=(const CircleObject &other) const {
    return !(*this == other);
}

float CircleObject::getX() const { return m_position.x; }

float CircleObject::getY() const { return m_position.y; }

float CircleObject::getRadius() const { return m_radius; }

sf::Vector2f CircleObject::getPosition() const { return m_position; }

bool CircleObject::inside(const sf::Vector2f point) const {
    const float x = point.x - m_position.x;
    const float y = point.y - m_position.y;
    return x * x + y * y - m_radius * m_radius < +GameConstants::EPS;
}
