#include "core/bot/EasyLinearBotStrategy.h"


Expression EasyLinearBotStrategy::calculateExpression(const std::shared_ptr<Player> &bot,
                                                      const std::vector<std::shared_ptr<Player> > &players,
                                                      const std::vector<std::shared_ptr<Obstacle> > &obstacles) {
    float lineAngle = 0;

    Expression res;

    res.add({TokenType::Variable, "x"});


    int index;
    do {
        index = Rng::getInt(0, static_cast<int>(players.size()) - 1);
    } while (*players[index] == *bot || !players[index]->isAlive());

    float dx = Rng::getFloat(-3, 3);

    sf::Vector2f origin = bot->getPosition();

    sf::Vector2f point = players[index]->getPosition();

    lineAngle = (point.y - origin.y) / (point.x - origin.x);


    res.add({TokenType::Constant, std::to_string(lineAngle * dx)});
    res.add({TokenType::BinaryOperator, "*"});

    return res;
}
