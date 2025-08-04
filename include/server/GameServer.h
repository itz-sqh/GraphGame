#pragma once
#include "ServerNetwork.h"
#include "core/Game.h"

class GameServer {
public:
    explicit GameServer(uint16_t port);
    void run();

private:
    void handleNewSession(ServerSession::ptr session);
    void handleMessage(int playerId, const NetworkMessage& msg);
    void broadcastWorldState();

    ServerNetwork network;
    Game game;
    std::unordered_map<ServerSession::ptr, int> sessionPlayerMap;
    int currentPlayerId = -1;
};