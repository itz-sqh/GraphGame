#include "objects/Player.h"



Player::Player(sf::Vector2f position, sf::Color color, float radius)
        : CircleObject(position,radius), color(color) {}


void Player::draw(sf::RenderTarget &target) const {
    if (gotHit) return;
    const sf::Vector2u size = target.getSize();
    const float windowRadius = Geometry::mapToWindow(radius+GameConstants::MIN_X,size.x);
    if (isCurrentPlayer) {
        sf::CircleShape outerRing(2 * windowRadius);
        outerRing.setFillColor(sf::Color::White);
        outerRing.setOutlineThickness(2);
        outerRing.setOutlineColor(color);
        outerRing.setOrigin({2 * windowRadius, 2 * windowRadius});
        outerRing.setPosition(Geometry::mapToWindow(position, size));
        target.draw(outerRing);
    }


    sf::CircleShape shape(windowRadius);
    shape.setFillColor(color);
    shape.setPosition(Geometry::mapToWindow(position, size));
    shape.setOrigin({windowRadius, windowRadius});
    target.draw(shape);
}

sf::Color Player::getColor() const {
    return color;
}
void Player::switchCurrent() {
    isCurrentPlayer = !isCurrentPlayer;
}

bool Player::isAlive() const {
    return !gotHit;
}

bool Player::isCurrent() const {
    return isCurrentPlayer;
}
void Player::kill() {
    gotHit = true;
}






