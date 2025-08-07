#include "ui/InputManager.h"

void InputManager::handleEvent(const sf::Event &event) {
    if (auto *textEvent = event.getIf<sf::Event::TextEntered>()) {
        if (textEvent->unicode == '\b' && !m_buffer.empty()) {
            m_buffer.pop_back();
        } else if (textEvent->unicode != '\b' && m_buffer.size() < GameConstants::MAX_INPUT_SIZE) {
            m_buffer += static_cast<char>(textEvent->unicode);
        }
        validateInput();
    }
}

void InputManager::clear() {
    m_buffer.clear();
    m_expr.reset();
}

void InputManager::validateInput() {
    if (auto parsed = ExpressionParser::parse(m_buffer)) m_expr = *parsed;
    else m_expr.reset();
}


void InputManager::addChar(char c) { m_buffer.push_back(c); }

const std::string &InputManager::getCurrentInput() const { return m_buffer; }

bool InputManager::isValidExpression() const { return m_expr.has_value(); }

std::optional<Expression> InputManager::getExpression() const { return m_expr; }
