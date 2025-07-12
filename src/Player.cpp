#include "Player.h"

Player::Player(sf::Vector2f position, sf::Color color, float radius)
        : position(position), gotHit(false), radius(radius), color(color) {}


void Player::draw(sf::RenderTarget &target, bool isCurrent) const {
    if (gotHit) return;
    sf::Vector2u size = target.getSize();
    if (isCurrent) {
        sf::CircleShape outerRing(2 * radius);
        outerRing.setFillColor(sf::Color::White);
        outerRing.setOutlineThickness(2);
        outerRing.setOutlineColor(color);
        outerRing.setOrigin({2 * radius, 2 * radius});
        outerRing.setPosition(mapToWindow(position, size));
        target.draw(outerRing);
    }


    sf::CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setPosition(mapToWindow(position, size));
    shape.setOrigin({radius, radius});
    target.draw(shape);
}

sf::Color Player::getColor() const {
    return color;
}

float Player::getX() const {
    return position.x;
}

float Player::getY() const {
    return position.y;
}

float Player::getRadius() const {
    return radius;
}

sf::Vector2f Player::getPosition() const {
    return position;
}

bool Player::isAlive() const {
    return !gotHit;
}





