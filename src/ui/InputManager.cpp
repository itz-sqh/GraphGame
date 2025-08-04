#include "ui/InputManager.h"

void InputManager::handleEvent(const sf::Event &event) {
    if (auto* textEvent = event.getIf<sf::Event::TextEntered>()) {
        if (textEvent->unicode == '\b' && !buffer.empty()) {
            buffer.pop_back();
        }
        else if (textEvent->unicode != '\b' && buffer.size() < GameConstants::MAX_INPUT_SIZE) {
            buffer += static_cast<char>(textEvent->unicode);
        }
        validateInput();
    }

}

void InputManager::clear() {
    buffer.clear();
    expr.reset();
}

void InputManager::validateInput() {
    if (auto parsed = ExpressionParser::parse(buffer)) expr = *parsed;
    else expr.reset();
}


void InputManager::setInput(const std::string &input) {
    buffer = input;
}

