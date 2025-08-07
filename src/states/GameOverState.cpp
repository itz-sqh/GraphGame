#include "states/GameOverState.h"


GameOverState::GameOverState(sf::Color winner, sf::Vector2u screenSize) : m_gameOverText(m_font, ""),
                                                                          m_winnerColor(winner) {
    if (!m_font.openFromFile("resources/ARIAL.TTF")) {
        // TODO handle errors
    }

    m_gameOverText.setFont(m_font);
    m_gameOverText.setString("Game over");

    m_gameOverText.setCharacterSize(60);
    m_gameOverText.setFillColor(sf::Color::Black);

    sf::FloatRect bounds = m_gameOverText.getLocalBounds();
    m_gameOverText.setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});

    m_gameOverText.setFont(m_font);
    m_gameOverText.setCharacterSize(40);


    m_gameOverText.setString("Press Enter/Escape/Space\n To return to main menu");

    m_gameOverText.setFillColor(m_winnerColor);

    m_gameOverText.setPosition({static_cast<float>(screenSize.x) / 2.f, static_cast<float>(screenSize.y) / 2.f});
}

void GameOverState::handleEvents(Game &game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }

        if (auto keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Escape ||
                keyEvent->code == sf::Keyboard::Key::Enter ||
                keyEvent->code == sf::Keyboard::Key::Space) {
                game.changeState(std::make_unique<StartMenuState>(game));
            }
        }
    }
}

void GameOverState::update(Game &game) {
    // No need
}

void GameOverState::render(Game &game) {
    auto &window = game.getWindow();
    window.clear(GameConstants::BACKGROUND_COLOR);

    window.draw(m_gameOverText);

    window.display();
}
