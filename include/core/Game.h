#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <stack>
#include "../states/GameState.h"
#include "World.h"
#include "ui/InputManager.h"
#include"states/InputState.h"

class Game {
public:
    Game();
    void run();
    void changeState(std::unique_ptr<GameState> state);
    void pushState(std::unique_ptr<GameState> state);
    void popState();

    [[nodiscard]] sf::RenderWindow& getWindow() const { return *window; }
    World& getWorld() { return world; }
    InputManager& getInputManager() { return inputManager; }

private:
    std::unique_ptr<sf::RenderWindow> window;
    World world;
    InputManager inputManager;
    std::stack<std::unique_ptr<GameState>> states;
};