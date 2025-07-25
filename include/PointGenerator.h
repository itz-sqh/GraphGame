#pragma once
#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "Expression.h"
#include "ExpressionParser.h"
#include "GameConstants.h"

class PointGenerator {
public:
    explicit PointGenerator(const std::string &expression);

    explicit PointGenerator(const Expression& expression);

    [[nodiscard]] std::vector<sf::Vector2f> getSegmentPoints(float leftX = GameConstants::MIN_X, float rightX = GameConstants::MAX_X) const;

private:


    [[nodiscard]] std::vector<sf::Vector2f> getY(const std::vector<float>& vecX) const;

    [[nodiscard]] sf::Vector2f getY(float x) const;
    Expression expression;
};

