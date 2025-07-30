#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include "core/GameConstants.h"
#include <cmath>
#include <boost/serialization/access.hpp>


class CircleObject {
public:
    explicit CircleObject(sf::Vector2f position, float radius);

    CircleObject() = default;

    bool operator==(const CircleObject &other) const;

    bool operator!=(const CircleObject &other) const;

    virtual ~CircleObject() = default;


    [[nodiscard]] bool inside(sf::Vector2f point) const;

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getRadius() const;

    [[nodiscard]] sf::Vector2f getPosition() const;

protected:
    sf::Vector2f position;
    float radius;
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int) {
        ar & position & radius;
    }
};
