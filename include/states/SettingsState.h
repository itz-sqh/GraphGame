#pragma once
#include "BaseState.h"
#include "ui/MenuContainer.h"
#include "core/GameConstants.h"
#include "ui/MenuTextItem.h"
#include "core/Game.h"

class SettingsState : public BaseState {
public:
    explicit SettingsState(Game &game);

    void handleEvents(Game &game) override;

    void update(Game &game) override;

    void render(Game &game) override;

private:
    Game &m_game;
    std::unique_ptr<MenuContainer> m_menu;
    sf::Font m_font;
    bool m_shouldExit = false;

    std::function<std::string()> textProvider;
};
