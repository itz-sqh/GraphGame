#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <optional>
#include <tuple>
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
        int centerIndex = 0;
        sf::Color color;
        std::vector<ObstacleHit> hitObstacles;
        std::vector<PlayerHit> hitPlayers;
    };

    static CollisionResult checkCollisions(
        const sf::VertexArray& vertices,
        sf::Vector2f origin,
        sf::Color color,
        const std::vector<std::shared_ptr<Obstacle>>& obstacles,
        const std::vector<std::shared_ptr<Player>>& players
    );

private:
    static std::tuple<int, std::optional<sf::Vector2f>, std::optional<std::shared_ptr<Obstacle>>>
    findLeftIntersection(
        const sf::VertexArray& vertices,
        const std::vector<std::shared_ptr<Obstacle>>& obstacles,
        int centerIndex,
        sf::Vector2f origin
    );

    static std::tuple<int, std::optional<sf::Vector2f>, std::optional<std::shared_ptr<Obstacle>>>
    findRightIntersection(
        const sf::VertexArray& vertices,
        const std::vector<std::shared_ptr<Obstacle>>& obstacles,
        int centerIndex,
        sf::Vector2f origin
    );

    static std::optional<std::tuple<sf::Vector2f, std::shared_ptr<Obstacle>>>
    findClosestIntersection(
        const std::vector<std::shared_ptr<Obstacle>>& obstacles,
        sf::Vector2f p1,
        sf::Vector2f p2,
        sf::Vector2f origin
    );

    static std::vector<std::tuple<sf::Vector2f, std::shared_ptr<Player>>>
    findPlayerHits(
        const sf::VertexArray& vertices,
        const std::vector<std::shared_ptr<Player>>& players,
        const sf::Vector2f& origin
    );
};
