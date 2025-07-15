#pragma once
#include <SFML/Graphics.hpp>
#include "PointGenerator.h"
#include "GameConstants.h"
#include "Obstacle.h"
#include "Player.h"
#include <vector>
#include <memory>
#include "Geometry.h"

class FunctionPlotter {
public:
    FunctionPlotter(const Expression& expr, sf::Color color);
    void update(const Expression& newExpr, sf::Color color);
    void draw(sf::RenderTarget& target,sf::Vector2f offset = {0,0});
private:
    void updatePoints();
    PointGenerator pointGenerator;
    sf::Vector2f minCoord;
    sf::Vector2f maxCoord;
    sf::Color color;
    sf::VertexArray vertices;

};