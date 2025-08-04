#pragma once
#include "ClientNetwork.h"
#include "core/Game.h"
#include "core/World.h"

class Client {
public:
    Client();

    void run(const std::string &ip, unsigned short port);

private:
    void handleInput();

    void render();

    void processMessage();


    ClientNetwork network;
    Game game;
    int playerId = -1;
    bool isCurrent = false;
};
