#include "math/Function.h"

Function::Function(const std::string &infix) {
    auto parseResult = ExpressionParser::parse(infix);
    if (!parseResult) this->m_expression = Expression();
    else this->m_expression = parseResult.value();
}

Function::Function(const Expression &expression) {
    this->m_expression = expression;
}


std::vector<sf::Vector2f> Function::generatePoints(float minX, float maxX) const {
    std::vector<sf::Vector2f> points;
    float currentX = minX;
    while (currentX <= maxX) {
        auto y = m_expression.evaluate(currentX);
        if (y) points.emplace_back(currentX, y.value());
        currentX += GameConstants::POINT_STEP;
    }
    return points;
}
