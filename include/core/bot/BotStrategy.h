#pragma once
#include "objects/Player.h"
#include "objects/Obstacle.h"

class BotStrategy {
public:
    virtual ~BotStrategy() = default;
    virtual Expression calculateExpression(
        const std::shared_ptr<Player>& bot,
        const std::vector<std::shared_ptr<Player>>& players,
        const std::vector<std::shared_ptr<Obstacle>>& obstacles
    ) = 0;
};