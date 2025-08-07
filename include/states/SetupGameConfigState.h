#pragma once
#include "BaseState.h"
#include "ui/MenuContainer.h"
#include "../core/ConfigManager.h"
#include "core/GameConstants.h"
#include "ui/MenuTextItem.h"
#include <algorithm>
#include "states/InputState.h"

class SetupGameConfigState : public BaseState {
public:
    SetupGameConfigState(Game &game, const ConfigManager &config);

    void handleEvents(Game &game) override;

    void update(Game &game) override;

    void render(Game &game) override;

private:
    Game &m_game;
    std::unique_ptr<MenuContainer> m_menu;
    int m_selectedPlayer = 0;
    sf::Font m_font;
    bool m_shouldExit = false;
    bool m_shouldStart = false;

private:
    void buildMenu();

    void startGame(Game &game);
};
