#pragma once
#include "NetworkObserver.h"
#include "NetworkService.h"
#include "core/Game.h"

// TODO come up with new architecture

class GameServer : public NetworkObserver {
public:
    GameServer(std::unique_ptr<NetworkService> networkService);

    void onMessageReceived(std::shared_ptr<Session> session,
                          const NetworkMessage& msg) override;

    void onClientConnected(std::shared_ptr<Session> session) override;

    void onClientDisconnected(std::shared_ptr<Session> session) override;

private:
    void processPlayerInput(std::shared_ptr<Session> session,
                           const std::string& input);

    void broadcastWorldSnapshot();

    std::unique_ptr<NetworkService> networkService;
    Game game;
    std::unordered_map<std::shared_ptr<Session>, std::string> playerInputs;
};