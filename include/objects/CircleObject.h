#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "core/GameConstants.h"
#include <cmath>


class CircleObject {
public:
    explicit CircleObject(sf::Vector2f position, float radius);

    bool operator==(const CircleObject &other) const;

    bool operator!=(const CircleObject &other) const;

    virtual ~CircleObject() = default;

    [[nodiscard]] bool inside(sf::Vector2f point) const;

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getRadius() const;

    [[nodiscard]] sf::Vector2f getPosition() const;

protected:
    sf::Vector2f m_position;
    float m_radius;
};
