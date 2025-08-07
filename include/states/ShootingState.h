#pragma once
#include "BaseState.h"
#include "objects/Projectile.h"
#include "core/Game.h"
#include "states/InputState.h"
#include "states/GameOverState.h"

class ShootingState : public BaseState {
public:
    void handleEvents(Game &game) override;

    void update(Game &game) override;

    void render(Game &game) override;

private:
    sf::Clock m_clock;
};
