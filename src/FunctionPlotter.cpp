#include "FunctionPlotter.h"
#include "Geometry.h"


FunctionPlotter::FunctionPlotter(const Expression &expr, sf::Color color)
        : pointGenerator(expr), color(color),needUpdate(true) {
    vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
    updatePoints();
}

void FunctionPlotter::update(const Expression &newExpr, sf::Color newColor) {
    pointGenerator = PointGenerator(newExpr);
    color = newColor;
    needUpdate = true;
    updatePoints();
}

void FunctionPlotter::draw(sf::RenderTarget &target,
                           const std::vector<std::shared_ptr<Obstacle>> &obstacles,
                           const std::vector<std::shared_ptr<Player>> &players,
                           sf::Vector2f playerPosition) {
    if (!needUpdate) {
        target.draw(vertices);
        return;
    }
    needUpdate = false;
    const sf::Vector2u size = target.getSize();
    int centerInd = getCenterIndex();

    if (abs(vertices[centerInd].position.y) > GameConstants::MAX_Y) {
        throw std::runtime_error("y(0) must fit on screen");
    }
    const sf::Vector2f offset = vertices[centerInd].position;
    playerPosition -= offset;

    sf::VertexArray graphForDrawing;
    graphForDrawing.setPrimitiveType(sf::PrimitiveType::LineStrip);

    killPlayers(players);
    auto [leftEnd, leftIntersection] = getLeftIndexAndIntersection(centerInd, obstacles, playerPosition);
    auto [rightEnd, rightIntersection] = getRightIndexAndIntersection(centerInd, obstacles, playerPosition);
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
    vertices = graphForDrawing;
    target.draw(vertices);
}


void FunctionPlotter::updatePoints() {
    vertices.clear();
    auto points = pointGenerator.getSegmentPoints(3 * GameConstants::MIN_X, 3 * GameConstants::MAX_X);
    for (const auto &point: points) {
        vertices.append(sf::Vertex(sf::Vector2f(point), color));
    }
}

int FunctionPlotter::getCenterIndex() {
    for (int i = 0; i < vertices.getVertexCount(); i++) {
        if (vertices[i].position.x >= 0)
            return i;
    }
    return (int) vertices.getVertexCount() - 1;
}

std::tuple<int, std::optional<sf::Vector2f>>
FunctionPlotter::getRightIndexAndIntersection(int centerInd, const std::vector<std::shared_ptr<Obstacle>> &obstacles,
                                              sf::Vector2f playerPosition) {
    int rightEnd = (int) vertices.getVertexCount() - 1;
    std::shared_ptr<Obstacle> intersectObstacle;
    std::optional<sf::Vector2f> rightIntersection;
    for (int i = centerInd; i < (int) vertices.getVertexCount() - 1; ++i) {
        sf::Vector2f p1 = vertices[i].position + playerPosition;
        sf::Vector2f p2 = vertices[i + 1].position + playerPosition;
        rightIntersection = intersectObstacles(obstacles, p1, p2, playerPosition, intersectObstacle);
        if (rightIntersection) {
            rightEnd = i;
            break;
        }
    }
    if (rightIntersection)
        intersectObstacle->addOverlap(rightIntersection.value());
    return {rightEnd, rightIntersection};
}

std::tuple<int, std::optional<sf::Vector2f>>
FunctionPlotter::getLeftIndexAndIntersection(int centerInd, const std::vector<std::shared_ptr<Obstacle>> &obstacles,
                                             sf::Vector2f playerPosition) {
    int leftEnd = 0;
    std::optional<sf::Vector2f> leftIntersection;
    std::shared_ptr<Obstacle> intersectObstacle;
    for (int i = centerInd; i > 0; --i) {
        sf::Vector2f p1 = vertices[i].position + playerPosition;
        sf::Vector2f p2 = vertices[i - 1].position + playerPosition;
        leftIntersection = intersectObstacles(obstacles, p1, p2, playerPosition, intersectObstacle);
        if (leftIntersection) {
            leftEnd = i - 1;
            break;
        }
    }
    if (leftIntersection)
        intersectObstacle->addOverlap(leftIntersection.value());
    return {leftEnd, leftIntersection};
}

void FunctionPlotter::killPlayers(const std::vector<std::shared_ptr<Player>> &players) {
    for (int i = 0; i < vertices.getVertexCount() - 1; i++) {
        auto p1 = vertices[i].position;
        auto p2 = vertices[i + 1].position;
        Geometry::Line line(p1, p2);
        for (const auto &player: players) {
            if (player->getIsCurrent()) continue;
            auto intersections = Geometry::circleLineIntersection(*player, line);
            for (const auto &point: intersections) {
                if (point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x)) {
                    player->kill();
                }
            }
        }
    }
}


std::optional<sf::Vector2f>
FunctionPlotter::intersectObstacles(const std::vector<std::shared_ptr<Obstacle>> &obstacles, sf::Vector2f p1,
                                    sf::Vector2f p2,
                                    sf::Vector2f playerPosition, std::shared_ptr<Obstacle> &intersectObstacle) {
    Geometry::Line line(p1, p2);
    std::optional<sf::Vector2f> intersection;
    for (auto &obstacle: obstacles) {
        auto intersections = Geometry::circleLineIntersection(*obstacle, line);
        for (auto &point: intersections) {
            if (point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x) && !obstacle->isOverlapped(point)) {
                if (!intersection ||
                    std::abs(playerPosition.x - point.x) < std::abs(playerPosition.x - intersection->x)) {
                    intersectObstacle = obstacle;
                    intersection = point;
                }
            }
        }
        std::vector<CircleObject> overlaps = obstacle->getOverlaps();
        for (auto &overlap: overlaps) {
            intersections = Geometry::circleLineIntersection(overlap, line);
            for (auto &point: intersections) {
                if (point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x)) {
                    if (!obstacle->isOverlapped(point, overlap)) {
                        if (!intersection ||
                            std::abs(playerPosition.x - point.x) < std::abs(playerPosition.x - intersection->x)) {
                            intersectObstacle = obstacle;
                            intersection = point;
                        }
                    }
                }
            }
        }
    }
    return intersection;
}


