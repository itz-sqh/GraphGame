#include "core/bot/HardLinearBotStrategy.h"


Expression HardLinearBotStrategy::calculateExpression(const std::shared_ptr<Player> &bot,
                                                      const std::vector<std::shared_ptr<Player> > &players,
                                                      const std::vector<std::shared_ptr<Obstacle> > &obstacles) {
    float lineAngle = 0;
    Expression res;

    res.add({TokenType::Variable, "x"});

    sf::Vector2f origin = bot->getPosition();

    std::vector<int> canKill, cantKill;

    for (int i = 0; i < players.size(); ++i) {
        const auto &player = players[i];
        if (*player == *bot || !player->isAlive() || player->getColor() == bot->getColor()) {
            continue;
        }

        if (CollisionManager::canHitPlayer(bot, player, obstacles)) {
            canKill.push_back(i);
        } else {
            cantKill.push_back(i);
        }
    }

    int index = -1;
    if (!canKill.empty()) {
        index = canKill[Rng::getInt(0, static_cast<int>(canKill.size()) - 1)];
    } else if (!cantKill.empty()) {
        index = cantKill[Rng::getInt(0, static_cast<int>(cantKill.size()) - 1)];
    }


    sf::Vector2f point = players[index]->getPosition();

    lineAngle = (point.y - origin.y) / (point.x - origin.x);


    res.add({TokenType::Constant, std::to_string(lineAngle)});
    res.add({TokenType::BinaryOperator, "*"});

    return res;
}
