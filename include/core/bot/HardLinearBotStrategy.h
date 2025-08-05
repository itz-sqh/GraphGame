#pragma once
#include "BotStrategy.h"

class HardLinearBotStrategy : public BotStrategy {
public:
    ~HardLinearBotStrategy() override = default;

    Expression calculateExpression(
        const std::shared_ptr<Player> &bot,
        const std::vector<std::shared_ptr<Player> > &players,
        const std::vector<std::shared_ptr<Obstacle> > &obstacles) override;
};
