#include "objects/Projectile.h"

Projectile::Projectile(const Expression &expr, sf::Color color, sf::Vector2f origin) : function(expr), color(color),
    origin(origin) {
    vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);

    auto points = function.generatePoints(3 * GameConstants::MIN_X, 3 * GameConstants::MAX_X);

    for (const auto &point: points) {
        vertices.append({origin + point, color});
    }
}


void Projectile::update(float dt,
                        std::vector<std::shared_ptr<Obstacle> > obstacles,
                        std::vector<std::shared_ptr<Player> > players) {
    if (!active) return;

    progress += dt / GameConstants::SHOT_DISPLAY_TIME;
    if (progress >= 1.f) {
        active = false;
    }
}

void Projectile::draw(sf::RenderTarget &target) const {
    if (!active) return;

    float elapsedTime = clock.getElapsedTime().asSeconds();
    int pointsToDraw = static_cast<int>(elapsedTime * GameConstants::POINTS_PER_SECOND);
    int centerIndex = Geometry::findCenterIndex(vertices, origin);

    int size = static_cast<int>(vertices.getVertexCount());

    sf::VertexArray visible(sf::PrimitiveType::LineStrip);

    int left = std::max(centerIndex - pointsToDraw, 0);
    int right = std::min(centerIndex + pointsToDraw, size - 1);
    for (int i = left; i <= right; i++) {
        visible.append(vertices[i]);
    }


    target.draw(visible);
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
