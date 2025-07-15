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


void FunctionPlotter::draw(sf::RenderTarget &target, const std::vector<std::unique_ptr<Obstacle>> &obstacles,
                           const sf::Vector2f playerPosition) {
    sf::Vector2f offset = playerPosition;
    const sf::Vector2u size = target.getSize();
    int centerInd = getCenterIndex(offset);
    sf::VertexArray graphForDrawing;
    graphForDrawing.setPrimitiveType(sf::PrimitiveType::LineStrip);
    if (vertices[centerInd].position.y == NAN) {
        throw std::runtime_error("The function must be defined when x = 0");
    }
    {//graph's left part
        int leftGoodInd = centerInd;
        std::optional<sf::Vector2f> leftIntersect;
        bool stopLeft = false;
        while (leftGoodInd != 0) {
            sf::Vector2f p1 = vertices[leftGoodInd].position;
            sf::Vector2f p2 = vertices[leftGoodInd - 1].position;
            for (auto &obstacle: obstacles) {
                auto intersectionPoints = Geometry::circleLineIntersection(*obstacle, Geometry::Line(p1, p2));
                for (auto &point: intersectionPoints) {
                    if (point.x >= std::max(p1.x, p2.x) || point.x <= std::min(p1.x, p2.x))
                        continue;
                    if (!leftIntersect.has_value() ||
                        abs(playerPosition.x - point.x) < abs(playerPosition.x - leftIntersect->x))
                        leftIntersect = point;
                    stopLeft = true;
                }
            }
            if (stopLeft)
                break;
            leftGoodInd -= 1;
        }
        if (leftIntersect.has_value())
            graphForDrawing.append(sf::Vertex(leftIntersect.value()));
        while (leftGoodInd != centerInd) {
            graphForDrawing.append(vertices[leftGoodInd]);
            leftGoodInd += 1;
        }
    }

    {//graph's right part
        int rightGoodInd = centerInd;
        std::optional<sf::Vector2f> rightIntersection;
        bool stopRight = false;
        while (rightGoodInd != vertices.getVertexCount()) {
            sf::Vector2f p1 = vertices[rightGoodInd].position;
            sf::Vector2f p2 = vertices[rightGoodInd + 1].position;
            for (auto &obstacle: obstacles) {
                auto intersectionPoints = Geometry::circleLineIntersection(*obstacle, Geometry::Line(p1, p2));
                for (auto &point: intersectionPoints) {
                    if (point.x >= std::max(p1.x, p2.x) || point.x <= std::min(p1.x, p2.x))
                        continue;
                    if (!rightIntersection.has_value() ||
                        abs(playerPosition.x - point.x) < abs(playerPosition.x - rightIntersection->x))
                        rightIntersection = point;
                    stopRight = true;
                }
            }
            if (stopRight)
                break;
            rightGoodInd += 1;
        }
        if (rightIntersection.has_value())
            graphForDrawing.append(sf::Vertex(rightIntersection.value()));
        while (rightGoodInd >= centerInd) {
            graphForDrawing.append(vertices[centerInd]);
            centerInd += 1;
        }
    }
    //TODO partition points into segments to not draw asymptotes by checking dy b/w points
    target.draw(graphForDrawing);
}

void FunctionPlotter::updatePoints() {
    vertices.clear();
    auto points = pointGenerator.getSegmentPoints(3 * GameConstants::MIN_X, 3 * GameConstants::MAX_X);
    for (const auto &point: points) {
        vertices.append(sf::Vertex(sf::Vector2f(point), color));
    }
}

int FunctionPlotter::getCenterIndex(sf::Vector2f position) {
    int left = 0, right = (int) vertices.getVertexCount();
    while (left + 1 != right) {
        int m = (left + right) / 2;
        bool condition = (vertices[m].position.x - position.x < 0);
        if (condition)
            left = m;
        else
            right = m;
    }
    return left;
}



