#include "CircleObject.h"



CircleObject::CircleObject(sf::Vector2f position, float radius) : position(position), radius(radius) {}


void CircleObject::draw(sf::RenderTarget &target) const {

}

bool CircleObject::operator==(const CircleObject &other) const {
    const float EPS = 1e-6;
    return abs(this->getX()-other.getX()) < EPS &&
        abs(this->getY()-other.getY()) < EPS &&
            abs(this->getRadius()-other.getRadius()) < EPS;
}

float CircleObject::getX() const { return position.x; }
float CircleObject::getY() const { return position.y; }
float CircleObject::getRadius() const { return radius; }
sf::Vector2f CircleObject::getPosition() const {return position;}
