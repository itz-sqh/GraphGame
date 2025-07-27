#include "objects/Projectile.h"

Projectile::Projectile(const Expression &expr, sf::Color color, sf::Vector2f origin) : function(expr), color(color),
    origin(origin) {
    vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);

    auto points = function.generatePoints(3 * GameConstants::MIN_X, 3 * GameConstants::MAX_X);

    for (const auto &point: points) {
        vertices.append({origin + point, color});
    }
    collidedVertices = vertices;
    centerIndex = Geometry::findCenterIndex(collidedVertices, origin);
    clock.restart();
}

void Projectile::update(float dt) {
    if (!active) return;
    progress += dt;
    pointsShown += dt * GameConstants::POINTS_PER_SECOND;
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


