#pragma once
#include <SFML/Graphics.hpp>
#include "../PointGenerator/PointGenerator.h"
#include"../GameConstants.h"

class FunctionPlotter {
public:
    FunctionPlotter(const Expression& expr, sf::Color color);
    void update(const Expression& newExpr, sf::Color color);
    void draw(sf::RenderTarget& target,const sf::Vector2f offset = {0,0});
private:
    void updatePoints();
    PointGenerator pointGenerator;
    sf::Vector2f minCoord;
    sf::Vector2f maxCoord;
    sf::Color color;
    sf::VertexArray vertices;

};