#include"Game.h"
#include<iostream>

int main()
{
    auto game = new Game();
    game->run();
    delete game;
}
