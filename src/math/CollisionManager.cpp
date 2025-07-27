#include "math/CollisionManager.h"

CollisionManager::CollisionResult CollisionManager::checkCollisions(
    const sf::VertexArray& vertices,
    sf::Vector2f origin,
    sf::Color color,
    const std::vector<std::shared_ptr<Obstacle>>& obstacles,
    const std::vector<std::shared_ptr<Player>>& players
) {
    CollisionResult res;
    res.vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);

    int centerIndex = Geometry::findCenterIndex(vertices, origin);
    if (centerIndex < 0) centerIndex = 0;

    auto leftResult = findLeftIntersection(vertices, obstacles, centerIndex, origin);
    auto rightResult = findRightIntersection(vertices, obstacles, centerIndex, origin);

    int leftEnd = std::get<0>(leftResult);
    int rightEnd = std::get<0>(rightResult);
    auto leftIntersection = std::get<1>(leftResult);
    auto rightIntersection = std::get<1>(rightResult);
    auto leftObstacle = std::get<2>(leftResult);
    auto rightObstacle = std::get<2>(rightResult);

    if (leftIntersection) {
        res.vertices.append(sf::Vertex(*leftIntersection, color));
        if (leftObstacle) {
            res.hitObstacles.push_back({*leftObstacle, *leftIntersection});
        }
    }

    for (int i = leftEnd; i <= rightEnd; ++i) {
        res.vertices.append(vertices[i]);
    }

    if (rightIntersection) {
        res.vertices.append(sf::Vertex(*rightIntersection, color));
        if (rightObstacle) {
            res.hitObstacles.push_back({*rightObstacle, *rightIntersection});
        }
    }

    res.centerIndex = centerIndex - leftEnd + (leftIntersection ? 1 : 0);

    auto playerHits = findPlayerHits(res.vertices, players, origin);
    for (const auto& [point, player] : playerHits) {
        res.hitPlayers.push_back({player,point});
    }


    return res;
}

std::tuple<int, std::optional<sf::Vector2f>, std::optional<std::shared_ptr<Obstacle>>>
CollisionManager::findLeftIntersection(
    const sf::VertexArray& vertices,
    const std::vector<std::shared_ptr<Obstacle>>& obstacles,
    int centerIndex,
    sf::Vector2f origin
) {
    int leftEnd = 0;
    std::optional<sf::Vector2f> intersection;
    std::optional<std::shared_ptr<Obstacle>> obstacle;

    for (int i = centerIndex; i > 0; --i) {
        sf::Vector2f p1 = vertices[i].position;
        sf::Vector2f p2 = vertices[i - 1].position;

        if (std::abs(p1.y) >= GameConstants::MAX_Y) {
            leftEnd = i;
            break;
        }

        auto res = findClosestIntersection(obstacles, p1, p2, origin);
        if (res) {
            intersection = std::get<0>(*res);
            obstacle = std::get<1>(*res);
            leftEnd = i;
            break;
        }
    }

    return {leftEnd, intersection, obstacle};
}

std::tuple<int, std::optional<sf::Vector2f>, std::optional<std::shared_ptr<Obstacle>>>
CollisionManager::findRightIntersection(
    const sf::VertexArray& vertices,
    const std::vector<std::shared_ptr<Obstacle>>& obstacles,
    int centerIndex,
    sf::Vector2f origin
) {
    int rightEnd = vertices.getVertexCount() - 1;
    std::optional<sf::Vector2f> intersection;
    std::optional<std::shared_ptr<Obstacle>> obstacle;

    for (int i = centerIndex; i < static_cast<int>(vertices.getVertexCount()) - 1; ++i) {
        sf::Vector2f p1 = vertices[i].position;
        sf::Vector2f p2 = vertices[i + 1].position;

        if (std::abs(p2.y) >= GameConstants::MAX_Y) {
            rightEnd = i;
            break;
        }

        auto res = findClosestIntersection(obstacles, p1, p2, origin);
        if (res) {
            intersection = std::get<0>(*res);
            obstacle = std::get<1>(*res);
            rightEnd = i;
            break;
        }
    }

    return {rightEnd, intersection, obstacle};
}

std::optional<std::tuple<sf::Vector2f, std::shared_ptr<Obstacle>>>
CollisionManager::findClosestIntersection(
    const std::vector<std::shared_ptr<Obstacle>>& obstacles,
    sf::Vector2f p1,
    sf::Vector2f p2,
    sf::Vector2f origin
) {
    std::optional<sf::Vector2f> closestIntersection;
    std::shared_ptr<Obstacle> closestObstacle;
    Geometry::Line line(p1, p2);

    for (auto& obstacle : obstacles) {
        auto intersections = Geometry::circleLineIntersection(*obstacle, line);
        for (auto& point : intersections) {
            if (point.x >= std::min(p1.x, p2.x) &&
                point.x <= std::max(p1.x, p2.x) &&
                !obstacle->isOverlapped(point)) {

                if (!closestIntersection ||
                    std::abs(origin.x - point.x) < std::abs(origin.x - closestIntersection->x)) {
                    closestIntersection = point;
                    closestObstacle = obstacle;
                }
            }
        }

        for (auto& overlap : obstacle->getOverlaps()) {
            auto overlapIntersections = Geometry::circleLineIntersection(overlap, line);
            for (auto& point : overlapIntersections) {
                if (point.x >= std::min(p1.x, p2.x) &&
                    point.x <= std::max(p1.x, p2.x) &&
                    !obstacle->isOverlapped(point, overlap)) {

                    if (!closestIntersection ||
                        std::abs(origin.x - point.x) < std::abs(origin.x - closestIntersection->x)) {
                        closestIntersection = point;
                        closestObstacle = obstacle;
                    }
                }
            }
        }
    }

    if (closestIntersection && closestObstacle) {
        return std::make_tuple(*closestIntersection, closestObstacle);
    }

    return std::nullopt;
}

std::vector<std::tuple<sf::Vector2f, std::shared_ptr<Player>>> CollisionManager::findPlayerHits(
    const sf::VertexArray& vertices,
    const std::vector<std::shared_ptr<Player>>& players,
    const sf::Vector2f& origin
) {
    std::vector<std::tuple<sf::Vector2f, std::shared_ptr<Player>>> hits;

    for (size_t i = 0; i < vertices.getVertexCount() - 1; ++i) {
        const auto& p1 = vertices[i].position;
        const auto& p2 = vertices[i + 1].position;
        Geometry::Line line(p1, p2);

        for (const auto& player : players) {
            if (player->getPosition() == origin) continue;

            auto intersections = Geometry::circleLineIntersection(*player, line);
            for (const auto& point : intersections) {
                if (Geometry::distToSegment(point, p1, p2) <= GameConstants::EPS) {
                    hits.emplace_back(point, player);
                    break;
                }
            }
        }
    }

    return hits;
}