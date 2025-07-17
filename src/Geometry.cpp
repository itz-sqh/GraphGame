
#include "Geometry.h"

#include <stdexcept>

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

    sf::Vector2f mapToWindow(const sf::Vector2f pos,
                                    const sf::Vector2u size) {
        float x = (pos.x - GameConstants::MIN_X) / (GameConstants::MAX_X - GameConstants::MIN_X);
        float y = (pos.y - GameConstants::MIN_Y) / (GameConstants::MAX_Y - GameConstants::MIN_Y);

        return {
            x * static_cast<float>(size.x),
            static_cast<float>(size.y) - y * static_cast<float>(size.y)
    };
    }
    float mapToWindow(float value, const sf::Vector2u size) {
        float s1 = size.y/(GameConstants::MAX_Y - GameConstants::MIN_Y);
        float s2 = size.x/(GameConstants::MAX_X - GameConstants::MIN_X);
        if (abs(s2-s1) > GameConstants::EPS) throw std::runtime_error("i dont wanna work w/ ellipses");
        return value * s1;
    }

    float dist(const sf::Vector2f p1, const sf::Vector2f p2) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    float distSq(const sf::Vector2f p1, const sf::Vector2f p2) {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }
    float distToSegment(sf::Vector2f point, sf::Vector2f seg1, sf::Vector2f seg2) {
        sf::Vector2f AB = seg2 - seg1;
        sf::Vector2f AP = point - seg1;

        float proj = (AP.x * AB.x + AP.y * AB.y) / (AB.x * AB.x + AB.y * AB.y);

        if (proj < 0.0f) {
            return dist(point, seg1);
        } else if (proj > 1.0f) {
            return dist(point,seg2);
        } else {
            sf::Vector2f h = seg1 + proj * AB;
            return dist(point,h);
        }
    }


    std::vector<sf::Vector2f> circleLineIntersection(const CircleObject& circle,Line line) {
        const float r = circle.getRadius();
        const sf::Vector2f offset = circle.getPosition();

        line.c += line.a * offset.x + line.b * offset.y;

        float x0 = -line.a*line.c + offset.x;
        float y0 = -line.b*line.c + offset.y;

        if (line.c*line.c > r*r + GameConstants::EPS) {
            return {};
        }

        if (abs(line.c*line.c - r*r) < GameConstants::EPS) {
            return {{x0,y0}};
        }

        float d = r*r-line.c*line.c;
        float mult = std::sqrt(d);

        float ax,ay,bx,by;
        ax = x0 + line.b*mult;
        bx = x0 - line.b*mult;
        ay = y0 - line.a*mult;
        by = y0 + line.a*mult;
        return {{ax,ay},{bx,by}};
    }
    std::vector<sf::Vector2f> circleIntersection(const CircleObject& circle1, const CircleObject& circle2) {
        const sf::Vector2f offset1 = circle1.getPosition();
        const float r1 = circle1.getRadius();
        const sf::Vector2f offset2 = circle2.getPosition();
        const float r2 = circle2.getRadius();
        const sf::Vector2f d = offset2 - offset1;

        const float a = -2 * d.x;
        const float b = -2 * d.y;
        const float c = d.x*d.x+d.y*d.y+r1*r1-r2*r2 - a*offset1.x - b*offset1.y;

        const Line line(a,b,c);

        return circleLineIntersection(circle2,line);
    }
}
