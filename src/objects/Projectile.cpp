#include "objects/Projectile.h"

#include <iostream>


Projectile::Projectile(const Expression &expr, sf::Color color, sf::Vector2f origin) : function(expr), color(color),
                                                                                       origin(origin) {
    vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);

    auto points = function.generatePoints(3 * GameConstants::MIN_X, 3 * GameConstants::MAX_X);

    int centerIndex = Geometry::findCenterIndex(points, {GameConstants::POINT_STEP,GameConstants::POINT_STEP});

    auto offset = points[centerIndex];

    for (const auto &point: points) {
        vertices.append({origin + point - offset, color});
    }

    collidedVertices = vertices;
    clock.restart();
}

void Projectile::update(float dt) {
    if (!active) return;

    pointsShown += dt * GameConstants::POINTS_PER_SECOND;
    progress += dt;

    triggerEvents(static_cast<int>(pointsShown));

    if (progress >= GameConstants::SHOT_DISPLAY_TIME) {
        active = false;
    }
}

void Projectile::draw(sf::RenderTarget &target) {
    if (!active) return;

    int totalPoints = collidedVertices.getVertexCount();
    int pointsToShow = static_cast<int>(pointsShown);

    int startIdx = std::max(0, centerIndex - pointsToShow);
    int endIdx = std::min(totalPoints - 1, centerIndex + pointsToShow);

    sf::VertexArray leftVisible(sf::PrimitiveType::LineStrip);
    sf::VertexArray rightVisible(sf::PrimitiveType::LineStrip);

    for (int i = centerIndex; i > startIdx; --i) {
        auto pos = Geometry::mapToWindow(collidedVertices[i].position, target.getSize());
        leftVisible.append({pos, collidedVertices[i].color});
    }

    for (int i = centerIndex + 1; i <= endIdx; ++i) {
        auto pos = Geometry::mapToWindow(collidedVertices[i].position, target.getSize());
        rightVisible.append({pos, collidedVertices[i].color});
    }

    target.draw(leftVisible);
    target.draw(rightVisible);
}

void Projectile::storeCollisionEvents(
      const std::vector<CollisionManager::PlayerHit>& players,
      const std::vector<CollisionManager::ObstacleHit>& obstacles,
      int centerIndex
  ) {
    hitEvents.clear();
    this->centerIndex = centerIndex;

    auto addEvent = [&](const sf::Vector2f& point, auto action) {
        int vertexIndex = findClosestVertexIndex(point);
        int distance = std::abs(vertexIndex - centerIndex);

        hitEvents.push_back({
            distance,
            false,
            action
        });
    };

    for (const auto& hit : players) {
        addEvent(hit.point, [player = hit.player] { player->kill(); });
    }

    for (const auto& hit : obstacles) {
        addEvent(hit.point, [obstacle = hit.obstacle, point = hit.point] {
            obstacle->addOverlap(point);
        });
    }

}

void Projectile::triggerEvents(int pointsShown) {
    for (auto& event : hitEvents) {
        if (!event.triggered && pointsShown >= event.index) {
            event.action();
            event.triggered = true;
        }
    }
}

int Projectile::findClosestVertexIndex(sf::Vector2f point) const {
    int res = 0;
    float minDistance = std::numeric_limits<float>::max();

    for (int i = 0; i < collidedVertices.getVertexCount(); ++i) {
        float dist = Geometry::dist(collidedVertices[i].position, point);
        if (dist < minDistance) {
            minDistance = dist;
            res = i;
        }
    }

    return res;
}


bool Projectile::isActive() const {
    return active;
}

const sf::VertexArray &Projectile::getVertices() const {
    return vertices;
}

const sf::Vector2f &Projectile::getOrigin() const {
    return origin;
}

void Projectile::setCenterIndex(int index) {
    centerIndex = index;
}
void Projectile::setCollidedVertices(const sf::VertexArray &vertices) {
    collidedVertices = vertices;
}


