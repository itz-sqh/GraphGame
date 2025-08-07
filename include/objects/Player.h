#pragma once
#include "expression/Expression.h"
#include <SFML/Graphics.hpp>
#include "CircleObject.h"
#include "core/GameConstants.h"
#include "math/Geometry.h"

class Player : public CircleObject {
public:
    Player(sf::Vector2f position, sf::Color color, float radius = GameConstants::PLAYER_RADIUS, bool isBot = false);

    void draw(sf::RenderTarget &target) const;

    ~Player() override = default;

    [[nodiscard]] bool isAlive() const;

    void kill();

    [[nodiscard]] sf::Color getColor() const;

    void switchCurrent();

    [[nodiscard]] bool isCurrent() const;

    [[nodiscard]] bool isBot() const { return m_isBot; }

private:
    bool m_gotHit = false;
    bool m_isBot = false;
    bool m_isCurrentPlayer = false;
    sf::Color m_color;
};
