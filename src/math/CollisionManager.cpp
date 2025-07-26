#include "math/CollisionManager.h"


CollisionManager::CollisionResult
CollisionManager::checkCollisions(const Projectile &projectile, const World &world) {
    CollisionResult res;

    const auto &vertices = projectile.getVertices();

    int centerIndex = Geometry::findCenterIndex(vertices, projectile.getOrigin());

    auto leftIntersection = findObstacleIntersection(
        vertices,
        world.getObstacles(),
        centerIndex,
        -1
    );
    auto rightIntersection = findObstacleIntersection(
        vertices,
        world.getObstacles(),
        centerIndex,
        1
    );

    int leftEnd = leftIntersection ? std::get<0>(leftIntersection.value()) : 0;
    int rightEnd = rightIntersection ? std::get<0>(rightIntersection.value()) : vertices.getVertexCount() - 1;

    if (leftIntersection) {
        res.vertices.append({std::get<1>(leftIntersection.value()), world.getCurrentPlayer()->getColor()});
        res.hitObstacles.emplace_back(std::get<2>(leftIntersection.value()));
    }
    for (int i = leftEnd; i <= rightEnd; ++i) {
        res.vertices.append(vertices[i]);
    }
    if (rightIntersection) {
        res.vertices.append({std::get<1>(rightIntersection.value()), world.getCurrentPlayer()->getColor()});
        res.hitObstacles.emplace_back(std::get<2>(rightIntersection.value()));
    }

    res.hitPlayers = findPlayerHits(
        res.vertices,
        world.getPlayers(),
        projectile.getOrigin()
    );

    return res;
}


std::optional<std::tuple<size_t, sf::Vector2f, std::shared_ptr<Obstacle> > >
CollisionManager::findObstacleIntersection(const sf::VertexArray &vertices,
                                           const std::vector<std::shared_ptr<Obstacle> > &obstacles, size_t startIdx,
                                           int direction) {
    for (int i = startIdx; i > 0 && i < vertices.getVertexCount() - 1; i += direction) {
        const auto &p1 = vertices[i].position;
        const auto &p2 = vertices[i + direction].position;
        const Geometry::Line line(p1, p2);

        for (const auto &obstacle: obstacles) {
            auto intersections = Geometry::circleLineIntersection(*obstacle, line);

            for (const auto &point: intersections) {
                if (point.x >= std::min(p1.x, p2.x) &&
                    point.x <= std::max(p1.x, p2.x) &&
                    !obstacle->isOverlapped(point)) {
                    return std::make_tuple(i, point, obstacle);
                }
            }
        }
    }
    return std::nullopt;
}


std::vector<std::shared_ptr<Player> > CollisionManager::findPlayerHits(const sf::VertexArray &vertices,
                                                                       const std::vector<std::shared_ptr<Player> > &
                                                                       players, const sf::Vector2f &origin) {
    std::vector<std::shared_ptr<Player> > hits;

    for (int i = 0; i < vertices.getVertexCount() - 1; ++i) {
        const auto &p1 = vertices[i].position;
        const auto &p2 = vertices[i + 1].position;
        const Geometry::Line line(p1, p2);

        for (const auto &player: players) {
            if (player->getPosition() == origin) continue;

            auto intersections = Geometry::circleLineIntersection(*player, line);
            for (const auto &point: intersections) {
                if (Geometry::distToSegment(point, p1, p2) <= GameConstants::EPS) {
                    hits.push_back(player);
                    break;
                }
            }
        }
    }

    return hits;
}
