#pragma once
#include "Geometry.h"
#include "core/World.h"

class CollisionManager {
public:
    struct CollisionResult {
        sf::VertexArray vertices;
        std::vector<std::shared_ptr<Player>> hitPlayers;
        std::vector<std::shared_ptr<Obstacle>> hitObstacles;
    };

    static CollisionResult checkCollisions(const Projectile& projectile, const World& world);
    
private:
    static std::optional<std::tuple<size_t, sf::Vector2f, std::shared_ptr<Obstacle>>> findObstacleIntersection(
        const sf::VertexArray& vertices,
        const std::vector<std::shared_ptr<Obstacle>>& obstacles,
        size_t startIdx,
        int direction // 1 for right and -1 for left
    );

    static std::vector<std::shared_ptr<Player>> findPlayerHits(
        const sf::VertexArray& vertices,
        const std::vector<std::shared_ptr<Player>>& players,
        const sf::Vector2f& origin
    );
};