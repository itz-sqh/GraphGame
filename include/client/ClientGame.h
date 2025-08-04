#pragma once
#include <cstdint>
#include <string>

#include "ClientSession.h"
#include "common/NetworkMessage.h"
#include "core/Game.h"

class ClientGame {
public:
    ClientGame();

    void run(const std::string& ip, uint16_t port);
    void handleMessage(const NetworkMessage& msg);

private:
    void processInput();
    void render();

    Game game;

    ClientSession session;
    int playerId = -1;

};
