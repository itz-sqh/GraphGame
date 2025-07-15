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

void FunctionPlotter::draw(sf::RenderTarget &target,
                         const std::vector<std::unique_ptr<Obstacle>>& obstacles,
                         const std::vector<std::shared_ptr<Player>>& players,
                         sf::Vector2f playerPosition) {
    const sf::Vector2u size = target.getSize();
    const int vertexCount = vertices.getVertexCount();
    int centerInd = getCenterIndex(playerPosition);

    if (abs(vertices[centerInd].position.y) > GameConstants::MAX_Y) {
        throw std::runtime_error("y(0) must fit on screen");
    }
    const sf::Vector2f offset = vertices[centerInd].position;
    playerPosition -= offset;

    sf::VertexArray graphForDrawing;
    graphForDrawing.setPrimitiveType(sf::PrimitiveType::LineStrip);

    int leftEnd = 0;
    std::optional<sf::Vector2f> leftIntersection;

    for (int i = centerInd; i > 0; --i) {
        sf::Vector2f p1 = vertices[i].position + playerPosition;
        sf::Vector2f p2 = vertices[i-1].position + playerPosition;
        Geometry::Line line(p1, p2);

        for (const auto& player : players) {
            if (player->getIsCurrent()) continue;
            auto intersections = Geometry::circleLineIntersection(*player,line);
            for (const auto& point : intersections) {
                if (point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x)) {
                    player->kill();
                }
            }
        }


        bool intersected = false;
        for (auto& obstacle : obstacles) {
            auto intersections = Geometry::circleLineIntersection(*obstacle, line);
            for (auto& point : intersections) {
                if (point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x)) {
                    leftIntersection = point;
                    obstacle->addOverlap(point);
                    leftEnd = i;
                    intersected = true;
                    break;
                }
            }
            if (intersected) break;
        }
        if (intersected) break;
    }

    int rightEnd = vertexCount - 1;
    std::optional<sf::Vector2f> rightIntersection;

    for (int i = centerInd; i < vertexCount - 1; ++i) {
        sf::Vector2f p1 = vertices[i].position + playerPosition;
        sf::Vector2f p2 = vertices[i+1].position + playerPosition;
        Geometry::Line line(p1, p2);

        for (const auto& player : players) {
            if (player->getIsCurrent()) continue;
            auto intersections = Geometry::circleLineIntersection(*player, line);
            for (const auto& point : intersections) {
                if (point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x)) {
                    player->kill();
                }
            }
        }

        bool intersected = false;
        for (auto& obstacle : obstacles) {
            auto intersections = Geometry::circleLineIntersection(*obstacle, line);
            for (auto& point : intersections) {
                if (point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x)) {
                    rightIntersection = point;
                    obstacle->addOverlap(point);
                    rightEnd = i;
                    intersected = true;
                    break;
                }
            }
            if (intersected) break;
        }
        if (intersected) break;
    }

    if (leftIntersection) {
        graphForDrawing.append(sf::Vertex(Geometry::mapToWindow(*leftIntersection, size), color));
    }

    for (int i = leftEnd; i <= rightEnd; ++i) {
        graphForDrawing.append(sf::Vertex(
            Geometry::mapToWindow(vertices[i].position + playerPosition, size),
            color
        ));
    }

    if (rightIntersection) {
        graphForDrawing.append(sf::Vertex(Geometry::mapToWindow(*rightIntersection, size), color));
    }
    //TODO remove asymptotes
    //TODO allow graph to go past overlap
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
    for (int i = 0; i < vertices.getVertexCount(); i++) {
        if (vertices[i].position.x >= 0)
            return i;
    }
    return vertices.getVertexCount() - 1;
}



