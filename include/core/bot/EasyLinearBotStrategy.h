#pragma once
#include "BotStrategy.h"
#include "math/Rng.h"

class EasyLinearBotStrategy : public BotStrategy {
public:
    ~EasyLinearBotStrategy() override = default;
    Expression calculateExpression(
        const std::shared_ptr<Player> &bot,
        const std::vector<std::shared_ptr<Player> > &players,
        const std::vector<std::shared_ptr<Obstacle> > &obstacles) override;
};
