#pragma once

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../ExpressionParser/Expression.h"
#include "../ExpressionParser/ExpressionParser.h"
#include "../GameConstants.h"

class PointGenerator {
public:
    explicit PointGenerator(const std::string &expression);

    [[nodiscard]] std::vector<sf::Vector2<double>> GetSegmentPoints(double leftX, double rightX);

    [[nodiscard]] std::vector<sf::Vector2<double>> GetY(const std::vector<double>& x);

    [[nodiscard]] sf::Vector2<double> GetY(double x);

private:
    Expression expression;
};

