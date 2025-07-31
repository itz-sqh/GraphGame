#pragma once
#include <SFML/Window/Event.hpp>
#include <string>
#include "expression/ExpressionParser.h"
#include "core/GameConstants.h"

class InputManager {
public:
    void handleEvent(const sf::Event& event);
    void clear();

    [[nodiscard]] const std::string& getCurrentInput() const { return buffer; }
    [[nodiscard]] bool isValidExpression() const { return expr.has_value(); }
    [[nodiscard]] std::optional<Expression> getExpression() const { return expr; }
    [[nodiscard]] std::string getBuf() const {return buffer;}


private:
    std::string buffer;
    std::optional<Expression> expr;

    void validateInput();
};