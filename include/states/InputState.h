#pragma once
#include "BaseState.h"
#include "ui/InputBox.h"
#include <SFML/Window/Event.hpp>
#include "core/Game.h"
#include "states/ShootingState.h"

class InputState : public BaseState {
public:
    void handleEvents(Game &game) override;

    void update(Game &game) override;

    void render(Game &game) override;
};
