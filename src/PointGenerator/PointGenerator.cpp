#include "PointGenerator.h"

PointGenerator::PointGenerator(const std::string &expression) {
    this->expression = ExpressionParser::parse(expression);
}

std::vector<sf::Vector2<double>>
PointGenerator::GetSegmentPoints(double leftX, double rightX) {
    if (leftX >= rightX)
        throw std::runtime_error("Method GetSegmentPoints requires leftX<Right");

    std::vector<sf::Vector2<double>> result;

    double currentX = leftX;
    std::optional<double> currentY;
    while (currentX < rightX) {
        currentY = this->expression.evaluate(currentX);

        if (currentY.has_value())
            result.emplace_back(currentX, currentY.value());

        currentX += GameConstants::POINTS_STEP;
    }

    currentX = rightX;
    currentY = this->expression.evaluate(currentX);
    if (currentY.has_value())
        result.emplace_back(currentX, currentY.value());

    return result;
}

sf::Vector2<double> PointGenerator::GetY(double x) {
    std::optional<double> y = this->expression.evaluate(x);

    if (!y.has_value())
        throw std::runtime_error("he value at the point is indeterminate");

    return {x, y.value()};
}

std::vector<sf::Vector2<double>> PointGenerator::GetY(const std::vector<double>& vecX) {

    std::vector<sf::Vector2<double>> result;
    for (auto x: vecX) {
        std::optional<double> y = this->expression.evaluate(x);

        if (!y.has_value())
            throw std::runtime_error("The value at the point is indeterminate");

        result.emplace_back(x, y.value());
    }
    return result;
}

