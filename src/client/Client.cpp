#include"client/Client.h"
#include"ui/InputManager.h"

void Client::run(const std::string &ip, unsigned short port) {
    if (!network.connect(ip, port)) return;

    game.getWindow().create(sf::VideoMode({GameConstants::WIDTH, GameConstants::HEIGHT}), "Graph Game");

    while (game.getWindow().isOpen()) {
        handleInput();
        processMessage();
        render();
    }
}

void Client::processMessage() {
    NetworkMessage msg;
    while (network.poolMessage(msg)) {
        switch (msg.type) {
            case PLAYER_ASSIGNMENT:
                playerId = msg.playerId;
                break;
            case WORLD_SNAPSHOT:
                game.applySnapshot(msg.get<WorldSnapshot>());
                isCurrent = game.getWorld().getCurrentPlayerId() == playerId;
                break;
            default:
                //TODO handle wrong message type
                break;
        }
    }
}


void Client::handleInput() {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }

        if (isCurrent) {
            // TODO merge into input manager
            game.getInputManager().handleEvent(event);
            if (auto *keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Enter) {
                    std::string input = game.getInputManager().getCurrentInput();

                    NetworkMessage msg = NetworkMessage::CreatePlayerInput(input);

                    network.send(msg);
                }
            }
        }
    }
}


void Client::render() {
    game.getWindow().clear(sf::Color::White);
    game.getWorld().draw(game.getWindow());

    // TODO render all stuff
}
