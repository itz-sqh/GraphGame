#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <optional>
#include "objects/Obstacle.h"
#include "objects/Player.h"
#include "math/Geometry.h"
#include "core/GameConstants.h"

class CollisionManager {
public:
    struct ObstacleHit {
        std::shared_ptr<Obstacle> obstacle;
        sf::Vector2f point;
    };
    
    struct PlayerHit {
        std::shared_ptr<Player> player;
        sf::Vector2f point;
    };

    struct CollisionResult {
        sf::VertexArray vertices;
        int centerIndex{};
        std::vector<ObstacleHit> hitObstacles;
        std::vector<PlayerHit> hitPlayers;
    };

    struct IntersectionResult {
        int index{};
        std::optional<sf::Vector2f> intersectionPoint;
        std::optional<std::shared_ptr<Obstacle>> obstacle;
    };

    static CollisionResult checkCollisions(
        const sf::VertexArray& vertices,
        sf::Vector2f origin,
        sf::Color color,
        const std::vector<std::shared_ptr<Obstacle>>& obstacles,
        const std::vector<std::shared_ptr<Player>>& players
    );
    static bool canHitPlayer(
        const std::shared_ptr<Player>& player1,
        const std::shared_ptr<Player>& player2,
        const std::vector<std::shared_ptr<Obstacle>>& obstacles
    );

private:
    enum class SearchDirection {Left,Right};
    static IntersectionResult findIntersection(
       const sf::VertexArray& vertices,
       const std::vector<std::shared_ptr<Obstacle>>& obstacles,
       int centerIndex,
       sf::Vector2f origin,
       SearchDirection direction
   );

    static std::vector<std::tuple<sf::Vector2f, std::shared_ptr<Player>>>
    findPlayerHits(
        const sf::VertexArray& vertices,
        const std::vector<std::shared_ptr<Player>>& players,
        const sf::Vector2f& origin
    );
};