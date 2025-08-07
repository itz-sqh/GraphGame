#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <stack>
#include "states/BaseState.h"
#include "World.h"
#include "ui/InputManager.h"
#include "states/InputState.h"
#include "states/StartMenuState.h"

class Game {
public:
    Game();

    void run();

    void changeState(std::unique_ptr<BaseState> state);

    void pushState(std::unique_ptr<BaseState> state);

    void popState();

    void initWorld();

    void cleanWorld();


    [[nodiscard]] sf::RenderWindow &getWindow() const { return *m_window; }
    World &getWorld() const { return *m_world; }
    InputManager &getInputManager() { return m_inputManager; }
    InputBox &getInputBox() { return m_inputBox; }
    ConfigManager &getConfigManager() { return m_configManager; }

private:
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<World> m_world;
    InputManager m_inputManager;
    InputBox m_inputBox;
    std::stack<std::unique_ptr<BaseState> > m_states;
    ConfigManager m_configManager;


    void recreateWindow();
};
