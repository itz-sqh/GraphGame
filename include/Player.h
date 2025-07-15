#pragma once
#include "Expression.h"
#include <SFML/Graphics.hpp>
#include "CircleObject.h"
#include "GameConstants.h"
#include "Geometry.h"

class Player : public CircleObject {
public:
    Player(sf::Vector2f position, sf::Color color, float radius = GameConstants::PLAYER_RADIUS);

    void draw(sf::RenderTarget& target) const;

    ~Player() override = default;

    [[nodiscard]] bool isAlive() const;
    void kill();
    [[nodiscard]] sf::Color getColor() const;
    void switchCurrent();

    bool getIsCurrent() const;

private:
    bool gotHit = false;
    bool isCurrent = false;
    sf::Color color;
};