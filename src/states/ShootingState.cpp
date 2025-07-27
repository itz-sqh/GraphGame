#include "states/ShootingState.h"

void ShootingState::handleEvents(Game &game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>())
            game.getWindow().close();
    }
}

void ShootingState::update(Game &game) {
    float dt = 1.0f/60.0f;
    game.getWorld().update(dt);

    if (!game.getWorld().isProjectileActive())
        game.changeState(std::make_unique<InputState>());
}

void ShootingState::render(Game& game) {
    game.getWindow().clear(sf::Color::White);
    game.getWorld().draw(game.getWindow());

    InputBox& box = game.getInputBox();
    game.getInputManager().clear();
    box.drawInactive(game.getWindow(), game.getInputManager().getCurrentInput());

    game.getWindow().display();
}



