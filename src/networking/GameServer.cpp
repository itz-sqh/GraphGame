#include "networking/GameServer.h"

GameServer::GameServer(std::unique_ptr<NetworkService> networkService) : networkService(std::move(networkService)) {
    this->networkService->registerObserver(this);
    this->networkService->start();
}

void GameServer::onMessageReceived(std::shared_ptr<Session> session, const NetworkMessage &msg) {
    switch (msg.type) {
        case MessageType::PLAYER_INPUT:
            if (auto input = msg.get<std::string>())
                processPlayerInput(session, *input);
            break;
        default:
            std::cerr << "Unknown message type received" << std::endl;
            break;
    }
}

void GameServer::onClientConnected(std::shared_ptr<Session> session) {
    broadcastWorldSnapshot();
}

void GameServer::onClientDisconnected(std::shared_ptr<Session> session) {
    playerInputs.erase(session);
    broadcastWorldSnapshot();
}


void GameServer::processPlayerInput(std::shared_ptr<Session> session, const std::string& input) {
    auto& currentState = game.getStates().top();

    if (typeid(*currentState) != typeid(InputState)) {
        sendError(session, "Input is not allowed in current state");
        return;
    }

    auto res = ExpressionParser::parse(input);
    if (!res || !res->isValid()) {
        sendError(session, "Invalid expression");
        return;
    }

    auto playerId = getPlayerId(session);
    pendingInputs[playerId] = *res;

    for (auto& [id, expr] : pendingInputs) {
        if (!game.getWorld().isProjectileActive())
            game.getWorld().fireProjectile(expr,game.getWorld().getPlayers()[id]->getColor());
    }

    pendingInputs.clear();

    game.changeState(std::make_unique<ShootingState>());

    broadcastWorldSnapshot();

}

void GameServer::broadcastWorldSnapshot() {
    WorldSnapshot snapshot(
        game.getWorld().getPlayers(),
        game.getWorld().getObstacles(),
        game.getWorld().isGameOver(),
        game.getInputManager().getCurrentInput(),
        game.getWorld().getProjectile()
    );
    NetworkMessage msg = NetworkMessage::create_world_snapshot(snapshot);
    networkService->broadcast(msg);
}


