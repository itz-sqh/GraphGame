#pragma once

class Game;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleEvents(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void render(Game& game) = 0;
};