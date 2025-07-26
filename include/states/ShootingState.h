#pragma once
#include "GameState.h"
#include "objects/Projectile.h"

class ShootingState : public GameState {
public:
    void handleEvents(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;
};
