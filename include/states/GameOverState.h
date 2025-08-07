#pragma once
#include "BaseState.h"
#include <SFML/Graphics/Text.hpp>
#include<SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "core/Game.h"
#include "core/GameConstants.h"
#include "states/StartMenuState.h"

class GameOverState : public BaseState {
public:
    explicit GameOverState(sf::Color winner, sf::Vector2u screenSize);

    void handleEvents(Game &game) override;

    void update(Game &game) override;

    void render(Game &game) override;

private:
    sf::Text m_gameOverText;
    sf::Font m_font;
    sf::Color m_winnerColor;
};
