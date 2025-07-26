#pragma once
#include "GameState.h"
#include "ui/InputBox.h"

class InputState : public GameState {

    void handleEvents(Game &game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    InputBox inputBox;
};