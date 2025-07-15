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

    void draw(sf::RenderTarget &target, const std::vector<std::unique_ptr<Obstacle>>& obstacles,
    const std::vector<std::shared_ptr<Player>>& players, sf::Vector2f offset = {0, 0});


private:
    void updatePoints();
    int getCenterIndex(sf::Vector2f position);
    PointGenerator pointGenerator;
    sf::Vector2f minCoord;
    sf::Vector2f maxCoord;
    sf::Color color;
    sf::VertexArray vertices;

};