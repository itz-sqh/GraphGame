#pragma once

#include <SFML/Graphics.hpp>
#include "PointGenerator.h"
#include "GameConstants.h"
#include "Obstacle.h"
#include "Player.h"
#include <vector>
#include <memory>
#include "Geometry.h"
#include <stdexcept>

class FunctionPlotter {
public:
    FunctionPlotter(const Expression &expr, sf::Color color);

    void update(const Expression &newExpr, sf::Color color);

    void draw(sf::RenderTarget &target, const std::vector<std::shared_ptr<Obstacle>> &obstacles,
              const std::vector<std::shared_ptr<Player>> &players, sf::Vector2f offset = {0, 0});




private:
    void updatePoints();

    int getCenterIndex();

    std::tuple<int, std::optional<sf::Vector2f>>
    getLeftIndexAndIntersection(int centerInd, const std::vector<std::shared_ptr<Obstacle>> &obstacles,sf::Vector2f offset = {0, 0});

    std::tuple<int, std::optional<sf::Vector2f>>
    getRightIndexAndIntersection(int centerInd, const std::vector<std::shared_ptr<Obstacle>> &obstacles,sf::Vector2f offset = {0, 0});

    void killPlayers(const std::vector<std::shared_ptr<Player>> &players);

    std::optional<sf::Vector2f>
    intersectObstacles(const std::vector<std::shared_ptr<Obstacle>> &obstacles, sf::Vector2f p1, sf::Vector2f p2,
                       sf::Vector2f playerPosition,std::shared_ptr<Obstacle>& intersectObstacle);
    PointGenerator pointGenerator;
    sf::Color color;
    sf::VertexArray vertices;

    bool needUpdate = false;

};