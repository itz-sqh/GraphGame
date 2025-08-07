#include "objects/Projectile.h"

Projectile::Projectile(const Expression &expr, sf::Color color, sf::Vector2f origin) : m_function(expr), m_color(color),
    m_origin(origin) {
    m_vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);

    auto points = m_function.generatePoints(3 * GameConstants::MIN_X, 3 * GameConstants::MAX_X);

    int centerIndex = Geometry::findCenterIndex(points, {GameConstants::POINT_STEP, GameConstants::POINT_STEP});

    auto offset = points[centerIndex];

    for (const auto &point: points) {
        m_vertices.append({origin + point - offset, color});
    }

    m_collidedVertices = m_vertices;
    m_clock.restart();
}

void Projectile::update(float dt) {
    if (!m_active) return;

    m_pointsShown += dt * GameConstants::POINTS_PER_SECOND;
    m_progress += dt;

    triggerEvents(static_cast<int>(m_pointsShown));

    if (m_progress >= GameConstants::SHOT_DISPLAY_TIME) {
        m_active = false;
    }
}

void Projectile::draw(sf::RenderTarget &target) {
    if (!m_active) return;

    int totalPoints = m_collidedVertices.getVertexCount();
    int pointsToShow = static_cast<int>(m_pointsShown);

    int startIdx = std::max(0, m_centerIndex - pointsToShow);
    int endIdx = std::min(totalPoints - 1, m_centerIndex + pointsToShow);

    sf::VertexArray leftVisible(sf::PrimitiveType::LineStrip);
    sf::VertexArray rightVisible(sf::PrimitiveType::LineStrip);

    for (int i = m_centerIndex; i > startIdx; --i) {
        auto pos = Geometry::mapToWindow(m_collidedVertices[i].position, target.getSize());
        leftVisible.append({pos, m_collidedVertices[i].color});
    }

    for (int i = m_centerIndex + 1; i <= endIdx; ++i) {
        auto pos = Geometry::mapToWindow(m_collidedVertices[i].position, target.getSize());
        rightVisible.append({pos, m_collidedVertices[i].color});
    }

    target.draw(leftVisible);
    target.draw(rightVisible);
}

void Projectile::storeCollisionEvents(
    const std::vector<CollisionManager::PlayerHit> &players,
    const std::vector<CollisionManager::ObstacleHit> &obstacles,
    int centerIndex
) {
    m_hitEvents.clear();
    this->m_centerIndex = centerIndex;

    auto addEvent = [&](const sf::Vector2f &point, auto action) {
        int vertexIndex = findClosestVertexIndex(point);
        int distance = std::abs(vertexIndex - centerIndex);

        m_hitEvents.push_back({
            distance,
            false,
            action
        });
    };

    for (const auto &hit: players) {
        addEvent(hit.point, [player = hit.player] { player->kill(); });
    }

    for (const auto &hit: obstacles) {
        addEvent(hit.point, [obstacle = hit.obstacle, point = hit.point] {
            obstacle->addOverlap(point);
        });
    }
}

void Projectile::triggerEvents(int pointsShown) {
    for (auto &event: m_hitEvents) {
        if (!event.triggered && pointsShown >= event.index) {
            event.action();
            event.triggered = true;
        }
    }
}

int Projectile::findClosestVertexIndex(sf::Vector2f point) const {
    int res = 0;
    float minDistance = std::numeric_limits<float>::max();

    for (int i = 0; i < m_collidedVertices.getVertexCount(); ++i) {
        float dist = Geometry::dist(m_collidedVertices[i].position, point);
        if (dist < minDistance) {
            minDistance = dist;
            res = i;
        }
    }

    return res;
}


bool Projectile::isActive() const {
    return m_active;
}

const sf::VertexArray &Projectile::getVertices() const {
    return m_vertices;
}

const sf::Vector2f &Projectile::getOrigin() const {
    return m_origin;
}

void Projectile::setCenterIndex(int index) {
    m_centerIndex = index;
}

void Projectile::setCollidedVertices(const sf::VertexArray &vertices) {
    m_collidedVertices = vertices;
}
