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

    explicit PointGenerator(const Expression& expression);

    [[nodiscard]] std::vector<sf::Vector2<double>> getSegmentPoints(double leftX = GameConstants::MIN_X, double rightX = GameConstants::MAX_X);

private:


    [[nodiscard]] std::vector<sf::Vector2<double>> getY(const std::vector<double>& x);

    [[nodiscard]] sf::Vector2<double> getY(double x);
    Expression expression;
};

