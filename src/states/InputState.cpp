#include "states/InputState.h"


void InputState::handleEvents(Game &game) {
    while (auto event = game.getWindow().pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            game.getWindow().close();
        }
        if (game.getWorld().getCurrentPlayer()->isBot()) break;

        if (event.has_value())
            game.getInputManager().handleEvent(event.value());

        if (auto keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Enter) {
                if (!game.getInputManager().isValidExpression()) {
                    game.getInputManager().clear();
                    // TODO show player what went wrong
                } else {
                    auto expression = game.getInputManager().getExpression();
                    game.getWorld().fireProjectile(*expression, game.getWorld().getCurrentPlayer()->getColor());
                    game.changeState(std::make_unique<ShootingState>());
                }
            }
        }
    }
}

void InputState::update(Game &game) {
    auto &world = game.getWorld();
    auto currentPlayer = world.getCurrentPlayer();


    if (currentPlayer->isBot()) {
        static bool calculating = false;
        static Expression botExpression;
        static sf::Clock botTimer;
        static std::string botInput;
        static bool typing;
        static size_t id = 0;

        if (!calculating && !typing) {
            botExpression = world.getBotManager().calculateExpression(currentPlayer, world.getPlayers(),
                                                                      world.getObstacles());
            botInput = botExpression.toString();

            calculating = true;
            botTimer.restart();
        } else if (calculating && botTimer.getElapsedTime().asSeconds() >= GameConstants::BOT_THINK_TIME) {
            calculating = false;
            typing = true;
            botTimer.restart();
            id = 0;
            game.getInputManager().clear();
        } else if (typing) {
            if (id < botInput.size()) {
                if (botTimer.getElapsedTime().asSeconds() >= GameConstants::BOT_TYPING_DELAY) {
                    game.getInputManager().addChar(botInput[id++]);
                    botTimer.restart();
                }
            }
            else if (botTimer.getElapsedTime().asSeconds() >=
                       GameConstants::BOT_POST_TYPING_DELAY) {
                world.fireProjectile(botExpression, currentPlayer->getColor());
                game.changeState(std::make_unique<ShootingState>());
                calculating = false;
                typing = false;
            }
        }
    }
}

void InputState::render(Game &game) {
    game.getWindow().clear(sf::Color::White);

    game.getWorld().draw(game.getWindow());

    inputBox.draw(game.getWindow(),
                  game.getInputManager().getCurrentInput(),
                  game.getWorld().getCurrentPlayer()->getColor());

    game.getWindow().display();
}
