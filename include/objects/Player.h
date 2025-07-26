#pragma once
#include "expression/Expression.h"
#include <SFML/Graphics.hpp>
#include "CircleObject.h"
#include "core/GameConstants.h"
#include "math/Geometry.h"

class Player : public CircleObject {
public:
    Player(sf::Vector2f position, sf::Color color, float radius = GameConstants::PLAYER_RADIUS);

    void draw(sf::RenderTarget& target) const;

    ~Player() override = default;

    [[nodiscard]] bool isAlive() const;
    void kill();
    [[nodiscard]] sf::Color getColor() const;
    void switchCurrent();

    bool isCurrent() const;

private:
    bool gotHit = false;
    bool isCurrentPlayer = false;
    sf::Color color;
};