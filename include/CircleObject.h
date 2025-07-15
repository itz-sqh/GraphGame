#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "GameConstants.h"


class CircleObject {
public:

    explicit CircleObject(sf::Vector2f position, float radius);

    bool operator==(const CircleObject &other) const;
    bool operator!=(const CircleObject &other) const;
    virtual ~CircleObject() = default;

    bool inside(sf::Vector2f point);
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getRadius() const;
    [[nodiscard]] sf::Vector2f getPosition() const;

protected:
    sf::Vector2f position;
    float radius;
};
