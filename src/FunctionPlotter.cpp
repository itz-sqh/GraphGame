#include "FunctionPlotter.h"

#include "Geometry.h"


FunctionPlotter::FunctionPlotter(const Expression &expr, sf::Color color)
        : pointGenerator(expr), color(color) {
    vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
    updatePoints();
}

void FunctionPlotter::update(const Expression &newExpr, sf::Color newColor) {
    pointGenerator = PointGenerator(newExpr);
    color = newColor;
    updatePoints();
}

void FunctionPlotter::draw(sf::RenderTarget &target, const sf::Vector2f offset) {
    const sf::Vector2u size = target.getSize();
    auto tmp = vertices;
    for (int i = 0; i < vertices.getVertexCount(); ++i) {
        tmp[i].position = Geometry::mapToWindow(vertices[i].position + offset, size);
    }
    target.draw(tmp);
}

void FunctionPlotter::updatePoints() {
    vertices.clear();
    auto points = pointGenerator.getSegmentPoints(3 * GameConstants::MIN_X, 3 * GameConstants::MAX_X);
    for (const auto &point: points) {
        vertices.append(sf::Vertex(sf::Vector2f(point), color));
    }
}





