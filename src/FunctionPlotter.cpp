#include "FunctionPlotter.h"


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

void FunctionPlotter::draw(sf::RenderTarget &target, sf::Vector2f offset) {
    const sf::Vector2u size = target.getSize();
    auto tmp = vertices;


    //TODO binary search first vertex with x > 0 and y not inf for correct alignment
    for (int i = 0; i < vertices.getVertexCount(); i++) {
        if (vertices[i].position.x >= 0 && abs(vertices[i].position.y) <= GameConstants::MAX_Y && abs(vertices[i].position.x) >= 0.5f) {
            offset -= vertices[i].position;
            break;
        }
    }
    //TODO partition points into segments to not draw asymptotes by checking dy b/w points
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





