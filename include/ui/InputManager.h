#pragma once
#include <SFML/Window/Event.hpp>
#include <string>
#include "expression/ExpressionParser.h"
#include "core/GameConstants.h"

class InputManager {
public:
    void handleEvent(const sf::Event &event);

    void clear();

    [[nodiscard]] const std::string &getCurrentInput() const;

    [[nodiscard]] bool isValidExpression() const;

    [[nodiscard]] std::optional<Expression> getExpression() const;

    void addChar(char c);

private:
    std::string m_buffer;
    std::optional<Expression> m_expr;

private:
    void validateInput();
};
