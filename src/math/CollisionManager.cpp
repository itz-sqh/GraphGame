#include "math/CollisionManager.h"

namespace {
    struct ObstacleIntersection {
        sf::Vector2f point;
        std::shared_ptr<Obstacle> obstacle;
    };


    std::optional<ObstacleIntersection> findClosestObstacleIntersection(
        const std::vector<std::shared_ptr<Obstacle> > &obstacles,
        const sf::Vector2f &p1,
        const sf::Vector2f &p2,
        const sf::Vector2f &origin
    ) {
        std::optional<ObstacleIntersection> closestIntersection;
        Geometry::Line segment(p1, p2);

        for (auto &obstacle: obstacles) {
            auto intersections = Geometry::circleLineIntersection(*obstacle, segment);
            for (auto &point: intersections) {
                if (Geometry::isPointInSegmentBounds(point, p1, p2) &&
                    !obstacle->isOverlapped(point)) {
                    if (!closestIntersection || std::abs(origin.x - point.x) < std::abs(
                            origin.x - closestIntersection->point.x)) {
                        closestIntersection = {point, obstacle};
                    }
                }
            }

            for (const auto &overlap: obstacle->getOverlaps()) {
                auto overlapIntersections = Geometry::circleLineIntersection(overlap, segment);
                for (auto &point: overlapIntersections) {
                    if (Geometry::isPointInSegmentBounds(point, p1, p2) &&
                        !obstacle->isOverlapped(point, overlap)) {
                        if (!closestIntersection ||
                            std::abs(origin.x - point.x) < std::abs(origin.x - closestIntersection->point.x)) {
                            closestIntersection = {point, obstacle};
                        }
                    }
                }
            }
        }

        return closestIntersection;
    }
}

CollisionManager::IntersectionResult CollisionManager::findIntersection(
    const sf::VertexArray &vertices,
    const std::vector<std::shared_ptr<Obstacle> > &obstacles,
    int centerIndex,
    sf::Vector2f origin,
    SearchDirection direction
) {
    IntersectionResult res;
    const int vertexCount = static_cast<int>(vertices.getVertexCount());
    res.index = (direction == SearchDirection::Left) ? 0 : vertexCount - 1;

    const int start = centerIndex;
    const int end = (direction == SearchDirection::Left) ? 0 : vertexCount - 1;
    const int step = (direction == SearchDirection::Left) ? -1 : 1;

    for (int i = start; i != end; i += step) {
        const sf::Vector2f &p1 = vertices[i].position;
        const sf::Vector2f &p2 = vertices[i + step].position;

        if ((direction == SearchDirection::Left && std::abs(p1.y) >= GameConstants::MAX_Y) ||
            (direction == SearchDirection::Right && std::abs(p2.y) >= GameConstants::MAX_Y)) {
            res.index = i;
            break;
        }

        const auto intersection = findClosestObstacleIntersection(obstacles, p1, p2, origin);
        if (intersection) {
            res.index = i;
            res.intersectionPoint = intersection->point;
            res.obstacle = intersection->obstacle;
            break;
        }
    }

    return res;
}

CollisionManager::CollisionResult CollisionManager::checkCollisions(
    const sf::VertexArray &vertices,
    sf::Vector2f origin,
    sf::Color color,
    const std::vector<std::shared_ptr<Obstacle> > &obstacles,
    const std::vector<std::shared_ptr<Player> > &players
) {
    CollisionResult res;
    res.vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);

    const int centerIndex = Geometry::findCenterIndex(vertices, origin);

    const auto leftIntersection = findIntersection(vertices, obstacles, centerIndex, origin, SearchDirection::Left);
    const auto rightIntersection = findIntersection(vertices, obstacles, centerIndex, origin, SearchDirection::Right);

    if (leftIntersection.intersectionPoint) {
        res.vertices.append(sf::Vertex(*leftIntersection.intersectionPoint, color));
        if (leftIntersection.obstacle) {
            res.hitObstacles.push_back({*leftIntersection.obstacle, *leftIntersection.intersectionPoint});
        }
    }

    for (int i = leftIntersection.index; i <= rightIntersection.index; ++i) {
        res.vertices.append(vertices[i]);
    }

    if (rightIntersection.intersectionPoint) {
        res.vertices.append(sf::Vertex(*rightIntersection.intersectionPoint, color));
        if (rightIntersection.obstacle) {
            res.hitObstacles.push_back({*rightIntersection.obstacle, *rightIntersection.intersectionPoint});
        }
    }

    res.centerIndex = centerIndex - leftIntersection.index + (leftIntersection.intersectionPoint ? 1 : 0);

    const auto playerHits = findPlayerHits(res.vertices, players, origin);
    for (const auto &[point, player]: playerHits) {
        res.hitPlayers.push_back({player, point});
    }

    return res;
}


std::vector<std::tuple<sf::Vector2f, std::shared_ptr<Player> > >
CollisionManager::findPlayerHits(
    const sf::VertexArray &vertices,
    const std::vector<std::shared_ptr<Player> > &players,
    const sf::Vector2f &origin
) {
    std::vector<std::tuple<sf::Vector2f, std::shared_ptr<Player> > > hits;

    for (size_t i = 0; i < vertices.getVertexCount() - 1; ++i) {
        const auto &p1 = vertices[i].position;
        const auto &p2 = vertices[i + 1].position;
        const Geometry::Line segment(p1, p2);

        for (const auto &player: players) {
            if (player->getPosition() == origin) continue;

            const auto intersections = Geometry::circleLineIntersection(*player, segment);
            for (const auto &point: intersections) {
                if (Geometry::distToSegment(point, p1, p2) <= GameConstants::EPS) {
                    hits.emplace_back(point, player);
                    break;
                }
            }
        }
    }

    return hits;
}

bool CollisionManager::canHitPlayer(
    const std::shared_ptr<Player> &player1,
    const std::shared_ptr<Player> &player2,
    const std::vector<std::shared_ptr<Obstacle> > &obstacles
) {
    const sf::Vector2f &p1 = player1->getPosition();
    const sf::Vector2f &p2 = player2->getPosition();

    auto intersection = findClosestObstacleIntersection(obstacles, p1, p2, p1);

    return !intersection.has_value();
}
