#include "../../include/states/ShootingState.h"

#include "../../include/core/Game.h"
#include "../../include/states/InputState.h"

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

void ShootingState::render(Game &game) {
    game.getWindow().clear(sf::Color::White);
    game.getWorld().draw(game.getWindow());
    game.getWindow().display();
}




