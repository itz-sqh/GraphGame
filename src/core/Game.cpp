#include "core/Game.h"

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(
        {GameConstants::WIDTH,GameConstants::HEIGHT}),
        "Graph Game"
        );
    window->setFramerateLimit(60);

    pushState(std::make_unique<InputState>());
}

void Game::run() {
    while (window->isOpen() && !world.isGameOver()) {
        states.top()->handleEvents(*this);
        states.top()->update(*this);
        states.top()->render(*this);
    }
}

void Game::changeState(std::unique_ptr<GameState> state) {
    if (!states.empty()) {
        states.pop();
    }
    states.push(std::move(state));
}

void Game::pushState(std::unique_ptr<GameState> state) {
    states.push(std::move(state));
}

void Game::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

void Game::applySnapshot(const WorldSnapshot &snapshot) {
    world = World(snapshot.players, snapshot.obstacles, snapshot.gameOver, snapshot.projectile);
    inputManager.setInput(snapshot.playerInput);
}



