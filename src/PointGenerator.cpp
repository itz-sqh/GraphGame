#include "PointGenerator.h"

PointGenerator::PointGenerator(const std::string &infix) {
    auto parseResult = ExpressionParser::parse(infix);
    if (!parseResult) this->expression = Expression();
    else this->expression = parseResult.value();
}

PointGenerator::PointGenerator(const Expression &expression) {
    this->expression = expression;
}


std::vector<sf::Vector2f>
PointGenerator::getSegmentPoints(float leftX, float rightX) const {
    if (leftX >= rightX)
        throw std::runtime_error("Method GetSegmentPoints requires leftX<Right");

    std::vector<sf::Vector2f> result;

    float currentX = leftX;
    std::optional<float> currentY;
    while (currentX < rightX) {
        currentY = this->expression.evaluate(currentX);

        result.emplace_back(currentX, currentY.value_or(NAN));

        currentX += GameConstants::POINT_STEP;
    }

    currentX = rightX;
    currentY = this->expression.evaluate(currentX);
    if (currentY.has_value())
        result.emplace_back(currentX, currentY.value());

    return result;
}

sf::Vector2f PointGenerator::getY(float x) const {
    std::optional<float> y = this->expression.evaluate(x);

    if (!y.has_value())
        throw std::runtime_error("he value at the point is indeterminate");

    return {x, y.value()};
}

std::vector<sf::Vector2f> PointGenerator::getY(const std::vector<float>& vecX) const {

    std::vector<sf::Vector2f> result;
    for (auto x: vecX) {
        std::optional<float> y = this->expression.evaluate(x);

        if (!y.has_value())
            throw std::runtime_error("The value at the point is indeterminate");

        result.emplace_back(x, y.value());
    }
    return result;
}

