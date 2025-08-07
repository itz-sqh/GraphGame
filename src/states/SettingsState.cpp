#include "states/SettingsState.h"


SettingsState::SettingsState(Game &game)
    : m_game(game), m_menu(std::make_unique<MenuContainer>()) {
    if (!m_font.openFromFile("resources/ARIAL.TTF")) {
        // TODO handle error
    }
    textProvider = [&]() {
        auto &config = m_game.getConfigManager();
        std::ostringstream oss;
        oss << "Resolution: " << config.getResolution().x << "x" << config.getResolution().y;
        return oss.str();
    };


    auto resolutionItem = std::make_unique<MenuTextItem>(
        m_font, 40, "", true, true
    );
    resolutionItem->setTextProvider(textProvider);

    resolutionItem->onAdjust = [&](int delta) {
        auto &config = m_game.getConfigManager();
        sf::Vector2u newSize = config.getResolution();

        if (delta > 0 && newSize.x + 320 < 1920) newSize += {320, 180};
        else if (delta < 0 && newSize.x - 320 >= 960) newSize -= {320, 180};

        config.setResolution(newSize);
    };

    auto backItem = std::make_unique<MenuTextItem>(
        m_font, 40, "Back", true, false
    );
    backItem->onActivate = [this] {
        m_game.getConfigManager().saveConfig();
        m_shouldExit = true;
    };

    m_menu->addComponent(std::move(resolutionItem));
    m_menu->addComponent(std::move(backItem));

    m_menu->setPosition({GameConstants::WIDTH / 2.f, GameConstants::HEIGHT / 3.f});

    m_menu->setSelectedIndex(0);
}

void SettingsState::handleEvents(Game &game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
        if (!event.has_value()) continue;
        m_menu->handleEvent(event.value());
    }
}

void SettingsState::update(Game &game) {
    m_menu->update();

    if (m_shouldExit) {
        game.popState();
    }
}

void SettingsState::render(Game &game) {
    auto &window = game.getWindow();
    window.clear(GameConstants::BACKGROUND_COLOR);
    m_menu->render(window);
    window.display();
}
