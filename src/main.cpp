#include "core/Game.h"

int main() {
    const auto game = new Game();
    game->run();
    delete game;
}
