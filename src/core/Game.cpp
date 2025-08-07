#include "core/Game.h"

Game::Game() {
    m_configManager.loadConfig();
    m_inputBox = InputBox(m_configManager);
    recreateWindow();
}

void Game::run() {
    changeState(std::make_unique<StartMenuState>(*this));

    while (m_window->isOpen()) {
        m_states.top()->handleEvents(*this);
        m_states.top()->update(*this);
        m_states.top()->render(*this);
    }
}

void Game::changeState(std::unique_ptr<BaseState> state) {
    if (!m_states.empty()) {
        m_states.pop();
    }
    m_states.push(std::move(state));
}

void Game::pushState(std::unique_ptr<BaseState> state) {
    m_states.push(std::move(state));
}

void Game::popState() {
    if (!m_states.empty()) {
        m_states.pop();
    }
}

void Game::initWorld() {
    cleanWorld();
    m_world = std::make_unique<World>(m_configManager);

    auto &botManager = m_world->getBotManager();

    for (int i = 0; i < m_configManager.getPlayerCount(); ++i) {
        if (m_configManager.getPlayerConfig(i).isBot)
            botManager.addBot(m_world->getPlayers()[i],
                              BotFactory::create(m_configManager.getPlayerConfig(i).difficulty));
    }
}

void Game::cleanWorld() {
    if (m_world) {
        m_world->clear();
    }
}

void Game::recreateWindow() {
    sf::Vector2u resolution = m_configManager.getResolution();

    m_window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(resolution),
        "Graph Game",
        sf::Style::Close
    );
    m_window->setFramerateLimit(60);
}
