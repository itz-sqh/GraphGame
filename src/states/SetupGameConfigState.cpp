#include "states/SetupGameConfigState.h"


SetupGameConfigState::SetupGameConfigState(Game &game, const ConfigManager &config)
    : m_game(game), m_menu(std::make_unique<MenuContainer>()) {
    if (!m_font.openFromFile("resources/ARIAL.TTF")) {
        // TODO handle error
    }
    buildMenu();
}

void SetupGameConfigState::buildMenu() {
    auto &config = m_game.getConfigManager();
    size_t index = m_menu ? m_menu->getSelectedIndex() : 0;
    m_menu = std::make_unique<MenuContainer>();


    auto playerCountItem = std::make_unique<MenuTextItem>(
        m_font, 24, "", true, true
    );
    playerCountItem->setTextProvider([&]() {
        return "Player Count: " + std::to_string(config.getPlayerCount());
    });
    playerCountItem->onAdjust = [&](int delta) {
        int oldPlayerCount = config.getPlayerCount();
        config.setPlayerCount(std::clamp(oldPlayerCount + delta, 2,
                                         static_cast<int>(std::size(GameConstants::PLAYER_COLOR))));
        if (config.getPlayerCount() != oldPlayerCount) {
            m_selectedPlayer = 0;
            buildMenu();
        }
    };
    m_menu->addComponent(std::move(playerCountItem));

    auto unitsItem = std::make_unique<MenuTextItem>(
        m_font, 24, "", true, true
    );
    unitsItem->setTextProvider([&]() {
        return "Units Per Player: " + std::to_string(config.getUnitsPerPlayer());
    });
    unitsItem->onAdjust = [&](int delta) {
        config.setUnitsPerPlayer(std::clamp(config.getUnitsPerPlayer() + delta, 1, 10));
    };
    m_menu->addComponent(std::move(unitsItem));

    auto obstacleItem = std::make_unique<MenuTextItem>(
        m_font, 24, "", true, true
    );
    obstacleItem->setTextProvider([&]() {
        return "Obstacle Count: " + std::to_string(config.getObstacleCount());
    });
    obstacleItem->onAdjust = [&](int delta) {
        config.setObstacleCount(std::clamp(config.getObstacleCount() + delta, 0, 50));
    };
    m_menu->addComponent(std::move(obstacleItem));

    auto separator1 = std::make_unique<MenuTextItem>(
        m_font, 24, "-----------------------------", false, false
    );
    m_menu->addComponent(std::move(separator1));

    auto playerIndex = std::make_unique<MenuTextItem>(
        m_font, 28, "", true, true
    );
    playerIndex->setTextProvider([&]() {
        return "Player: " + std::to_string(m_selectedPlayer + 1);
    });
    playerIndex->onAdjust = [&](int delta) {
        m_selectedPlayer = (m_selectedPlayer + delta + config.getPlayerCount()) % config.getPlayerCount();
        buildMenu();
    };
    m_menu->addComponent(std::move(playerIndex));

    auto typeItem = std::make_unique<MenuTextItem>(
        m_font, 24, "", true, true
    );
    typeItem->setTextProvider([&]() {
        PlayerConfig pc = config.getPlayerConfig(m_selectedPlayer);
        return "Type: " + std::string(pc.isBot ? "Bot" : "Human");
    });
    typeItem->onAdjust = [&](int delta) {
        PlayerConfig pc = config.getPlayerConfig(m_selectedPlayer);
        pc.isBot = !pc.isBot;
        config.setPlayerConfig(m_selectedPlayer, pc);
    };
    m_menu->addComponent(std::move(typeItem));

    auto diffItem = std::make_unique<MenuTextItem>(
        m_font, 24, "", true, true
    );
    diffItem->setTextProvider([&]() {
        PlayerConfig pc = config.getPlayerConfig(m_selectedPlayer);
        if (!pc.isBot) return "Difficulty: N/A";
        switch (pc.difficulty) {
            case BotFactory::Difficulty::EASY_LINEAR: return "Difficulty: Easy";
            case BotFactory::Difficulty::HARD_LINEAR: return "Difficulty: Hard";
            default: return "Difficulty: Unknown";
        }
    });
    diffItem->onAdjust = [&](int delta) {
        PlayerConfig pc = config.getPlayerConfig(m_selectedPlayer);
        if (pc.isBot) {
            int current = static_cast<int>(pc.difficulty);
            int next = (current + delta + 2) % 2;
            if (next < 0) next = 1;
            pc.difficulty = static_cast<BotFactory::Difficulty>(next);
            config.setPlayerConfig(m_selectedPlayer, pc);
        }
    };
    m_menu->addComponent(std::move(diffItem));

    auto separator2 = std::make_unique<MenuTextItem>(
        m_font, 24, "-----------------------------", false, false
    );
    m_menu->addComponent(std::move(separator2));

    auto startItem = std::make_unique<MenuTextItem>(
        m_font, 24, "Start Game", true, false
    );
    startItem->onActivate = [this]() {
        m_game.getConfigManager().saveConfig();
        m_shouldStart = true;
    };
    m_menu->addComponent(std::move(startItem));

    auto backItem = std::make_unique<MenuTextItem>(
        m_font, 24, "Back", true, false
    );
    backItem->onActivate = [this]() {
        m_game.getConfigManager().saveConfig();
        m_shouldExit = true;
    };
    m_menu->addComponent(std::move(backItem));

    m_menu->setPosition({GameConstants::WIDTH / 2.f, GameConstants::HEIGHT / 4.f});

    m_menu->setSelectedIndex(index);
}

void SetupGameConfigState::handleEvents(Game &game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
        if (!event.has_value()) continue;
        m_menu->handleEvent(event.value());
    }
}

void SetupGameConfigState::update(Game &game) {
    m_menu->update();

    if (m_shouldExit) {
        game.popState();
    } else if (m_shouldStart) {
        startGame(game);
    }
}

void SetupGameConfigState::render(Game &game) {
    auto &window = game.getWindow();
    window.clear(GameConstants::BACKGROUND_COLOR);
    m_menu->render(window);
    window.display();
}

void SetupGameConfigState::startGame(Game &game) {
    game.initWorld();
    game.changeState(std::make_unique<InputState>());
}
