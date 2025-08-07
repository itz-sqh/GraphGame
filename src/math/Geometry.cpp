#include "math/Geometry.h"


namespace Geometry {
    Line::Line(const sf::Vector2f p1, const sf::Vector2f p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -p1.x * a - p1.y * b;

        const float m = std::sqrt(a * a + b * b);

        a /= m;
        b /= m;
        c /= m;
    }

    Line::Line(const float a, const float b, const float c) : a(a), b(b), c(c) {
        const float m = std::sqrt(a * a + b * b);

        this->a /= m;
        this->b /= m;
        this->c /= m;
    }

    bool Line::equals(const Line &l1, const Line &l2) {
        return (std::abs(l1.a - l2.a) < GameConstants::EPS &&
                std::abs(l1.b - l2.b) < GameConstants::EPS &&
                std::abs(l1.c - l2.c) < GameConstants::EPS)
               ||
               (std::abs(l1.a + l2.a) < GameConstants::EPS &&
                std::abs(l1.b + l2.b) < GameConstants::EPS &&
                std::abs(l1.c + l2.c) < GameConstants::EPS);
    }


    sf::Vector2f mapToWindow(const sf::Vector2f pos, const sf::Vector2u size, float minX, float maxX, float minY,
                             float maxY) {
        const float x = (pos.x - minX) / (maxX - minX);
        const float y = (pos.y - minY) / (maxY - minY);

        return {
            x * static_cast<float>(size.x),
            static_cast<float>(size.y) - y * static_cast<float>(size.y)
        };
    }

    float mapToWindow(const float value, unsigned sizeX, float minX, float maxX) {
        const float s1 = (value - minX) / (maxX - minX);
        return static_cast<float>(sizeX) * s1;
    }

    float dist(const sf::Vector2f p1, const sf::Vector2f p2) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    float distSq(const sf::Vector2f p1, const sf::Vector2f p2) {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }

    float distToSegment(sf::Vector2f point, sf::Vector2f seg1, sf::Vector2f seg2) {
        const sf::Vector2f AB = seg2 - seg1;
        const sf::Vector2f AP = point - seg1;

        float proj = (AP.x * AB.x + AP.y * AB.y) / (AB.x * AB.x + AB.y * AB.y);

        if (proj < 0.f) return dist(point, seg1);
        else if (proj > 1.f) return dist(point, seg2);
        else {
            const sf::Vector2f h = seg1 + proj * AB;
            return dist(point, h);
        }
    }


    std::vector<sf::Vector2f> circleLineIntersection(const CircleObject &circle, Line line) {
        const float r = circle.getRadius();
        const sf::Vector2f offset = circle.getPosition();

        line.c += line.a * offset.x + line.b * offset.y;

        float x0 = -line.a * line.c + offset.x;
        float y0 = -line.b * line.c + offset.y;

        if (line.c * line.c > r * r + GameConstants::EPS) {
            return {};
        }

        if (std::abs(line.c * line.c - r * r) < GameConstants::EPS) {
            return {{x0, y0}};
        }

        const float d = r * r - line.c * line.c;
        const float mult = std::sqrt(d);

        float ax = x0 + line.b * mult;
        float bx = x0 - line.b * mult;
        float ay = y0 - line.a * mult;
        float by = y0 + line.a * mult;
        return {{ax, ay}, {bx, by}};
    }

    std::vector<sf::Vector2f> circleIntersection(const CircleObject &circle1, const CircleObject &circle2) {
        const sf::Vector2f offset1 = circle1.getPosition();
        const float r1 = circle1.getRadius();
        const sf::Vector2f offset2 = circle2.getPosition();
        const float r2 = circle2.getRadius();
        const sf::Vector2f d = offset2 - offset1;

        const float a = -2 * d.x;
        const float b = -2 * d.y;
        const float c = d.x * d.x + d.y * d.y + r1 * r1 - r2 * r2 - a * offset1.x - b * offset1.y;

        const Line line(a, b, c);

        return circleLineIntersection(circle2, line);
    }

    int findCenterIndex(const sf::VertexArray &vertices, sf::Vector2f position) {
        for (int i = 0; i < static_cast<int>(vertices.getVertexCount()); i++) {
            if (vertices[i].position.x >= position.x) {
                return i;
            }
        }
        return static_cast<int>(vertices.getVertexCount()) - 1;
    }

    int findCenterIndex(const std::vector<sf::Vector2f> &vertices, sf::Vector2f position) {
        for (int i = 0; i < static_cast<int>(vertices.size()); i++) {
            if (vertices[i].x >= position.x) {
                return i;
            }
        }
        return static_cast<int>(vertices.size()) - 1;
    }

    bool isPointInSegmentBounds(const sf::Vector2f &p,
                                const sf::Vector2f &seg1,
                                const sf::Vector2f &seg2) {
        const float minX = std::min(seg1.x, seg2.x);
        const float maxX = std::max(seg1.x, seg2.x);
        return (p.x >= minX && p.x <= maxX);
    }
}
