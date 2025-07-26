#pragma once
#include "expression/Expression.h"
#include"SFML/Graphics.hpp"
#include "Player.h"
#include "Obstacle.h"
#include "expression/Function.h"
#include "math/CollisionManager.h"


class Projectile {
public:
    Projectile(const Expression &expr, sf::Color color, sf::Vector2f origin);


    void Projectile::update(float dt,
                            std::vector<std::shared_ptr<Obstacle> > obstacles,
                            std::vector<std::shared_ptr<Player> > players);

    void draw(sf::RenderTarget &target) const;

    const sf::VertexArray &getVertices() const;

    const sf::Vector2f &getOrigin() const;

    [[nodiscard]] bool isActive() const;

private:
    Function function;
    sf::Color color;

    sf::Vector2f origin;

    float progress = 0.f;
    bool active = true;

    sf::VertexArray vertices;

    mutable sf::Clock clock;
    bool needUpdate = true;
};
