#include "states/InputState.h"


void InputState::handleEvents(Game &game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
        if (event.has_value())
            game.getInputManager().handleEvent(event.value());

        if (auto keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Enter) {
                if (!game.getInputManager().isValidExpression()) {
                    game.getInputManager().clear();
                    // TODO show player what went wrong
                }
                else {
                    auto expression = game.getInputManager().getExpression();
                    game.getWorld().fireProjectile(*expression, game.getWorld().getCurrentPlayer()->getColor());
                    game.changeState(std::make_unique<ShootingState>());
                }
            }
        }
    }
}

void InputState::update(Game &game) {
}

void InputState::render(Game &game) {
    game.getWindow().clear(sf::Color::White);

    game.getWorld().draw(game.getWindow());

    inputBox.draw(game.getWindow(),
                  game.getInputManager().getCurrentInput(),
                  game.getWorld().getCurrentPlayer()->getColor());

    game.getWindow().display();
}
