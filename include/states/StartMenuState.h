#pragma once
#include "BaseState.h"
#include "ui/MenuContainer.h"
#include "core/Game.h"
#include "core/GameConstants.h"
#include "ui/MenuTextItem.h"
#include "states/SettingsState.h"
#include "states/SetupGameConfigState.h"

class StartMenuState : public BaseState {
public:
    explicit StartMenuState(Game &game);

    void handleEvents(Game &game) override;

    void update(Game &game) override;

    void render(Game &game) override;

private:
    Game &m_game;
    std::unique_ptr<MenuContainer> m_menu;
    sf::Font m_font;
};
