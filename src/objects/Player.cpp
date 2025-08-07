#include "objects/Player.h"


Player::Player(sf::Vector2f position, sf::Color color, float radius, bool isBot)
    : CircleObject(position, radius), m_color(color), m_isBot(isBot) {
}


void Player::draw(sf::RenderTarget &target) const {
    if (m_gotHit) return;
    const sf::Vector2u size = target.getSize();
    const float windowRadius = Geometry::mapToWindow(m_radius + GameConstants::MIN_X, size.x);
    if (m_isCurrentPlayer && !m_isBot) {
        sf::CircleShape outerRing(2 * windowRadius);
        outerRing.setFillColor(sf::Color::White);
        outerRing.setOutlineThickness(2);
        outerRing.setOutlineColor(m_color);
        outerRing.setOrigin({2 * windowRadius, 2 * windowRadius});
        outerRing.setPosition(Geometry::mapToWindow(m_position, size));
        target.draw(outerRing);
    }


    sf::CircleShape shape(windowRadius);
    shape.setFillColor(m_color);
    shape.setPosition(Geometry::mapToWindow(m_position, size));
    shape.setOrigin({windowRadius, windowRadius});
    target.draw(shape);
}

sf::Color Player::getColor() const {
    return m_color;
}

void Player::switchCurrent() {
    m_isCurrentPlayer = !m_isCurrentPlayer;
}

bool Player::isAlive() const {
    return !m_gotHit;
}

bool Player::isCurrent() const {
    return m_isCurrentPlayer;
}

void Player::kill() {
    m_gotHit = true;
}
