#include "states/StartMenuState.h"

StartMenuState::StartMenuState(Game &game)
    : m_game(game), m_menu(std::make_unique<MenuContainer>()) {
    if (!m_font.openFromFile("resources/ARIAL.TTF")) {
        // TODO handle error
    }
    auto playItem = std::make_unique<MenuTextItem>(
        m_font, 40, "Play", true, false
    );
    playItem->onActivate = [&] {
        m_game.pushState(
            std::make_unique<SetupGameConfigState>(m_game, m_game.getConfigManager())
        );
    };

    auto settingsItem = std::make_unique<MenuTextItem>(
        m_font, 40, "Settings", true, false
    );
    settingsItem->onActivate = [&]() {
        m_game.pushState(std::make_unique<SettingsState>(m_game));
    };

    auto exitItem = std::make_unique<MenuTextItem>(
        m_font, 40, "Exit", true, false
    );
    exitItem->onActivate = [&]() {
        m_game.getWindow().close();
    };

    m_menu->addComponent(std::move(playItem));
    m_menu->addComponent(std::move(settingsItem));
    m_menu->addComponent(std::move(exitItem));

    m_menu->setPosition({GameConstants::WIDTH / 2.f, GameConstants::HEIGHT / 3.f});

    m_menu->setSelectedIndex(0);
}

void StartMenuState::handleEvents(Game &game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
        if (!event.has_value()) continue;
        m_menu->handleEvent(event.value());
    }
}

void StartMenuState::update(Game &game) {
    m_menu->update();
}

void StartMenuState::render(Game &game) {
    auto &window = game.getWindow();
    window.clear(GameConstants::BACKGROUND_COLOR);
    m_menu->render(window);
    window.display();
}
