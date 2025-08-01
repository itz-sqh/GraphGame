#pragma once
#include <string>
#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>
#include "expression/Expression.h"
#include "expression/ExpressionParser.h"
#include "core/GameConstants.h"

class Function {
public:
    explicit Function(const std::string &infix);

    explicit Function(const Expression& expression);

    [[nodiscard]] std::vector<sf::Vector2f> generatePoints(float minX = GameConstants::MIN_X, float maxX = GameConstants::MAX_X) const;


private:

    Expression expression;
};

