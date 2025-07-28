#pragma once
#include "expression/Expression.h"
#include"SFML/Graphics.hpp"
#include "Player.h"
#include "Obstacle.h"
#include "math/Function.h"
#include"math/CollisionManager.h"


class Projectile {
public:
    Projectile(const Expression &expr, sf::Color color, sf::Vector2f origin);

    void update(float dt);

    void draw(sf::RenderTarget &target);

    [[nodiscard]] const sf::VertexArray &getVertices() const;

    [[nodiscard]] const sf::Vector2f &getOrigin() const;

    [[nodiscard]] bool isActive() const;

    void setCollidedVertices(const sf::VertexArray &vertices);

    void setCenterIndex(int index);

    void triggerEvents(int pointsShown);

    void storeCollisionEvents(
          const std::vector<CollisionManager::PlayerHit>& players,
          const std::vector<CollisionManager::ObstacleHit>& obstacles,
          int centerIndex
      );

    int findClosestVertexIndex(sf::Vector2f point) const;

private:
    Function function;
    sf::Color color;
    sf::Vector2f origin;
    float progress = 0.f;
    bool active = true;
    sf::Clock clock;

    sf::VertexArray vertices;
    sf::VertexArray collidedVertices;
    int centerIndex = -1;

    float pointsShown = 0.f;

    struct HitEvent {
        int index;
        bool triggered = false;
        std::function<void()> action;
    };

    std::vector<HitEvent> hitEvents;
};
