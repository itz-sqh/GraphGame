#pragma once
#include "BotStrategy.h"


class BotManager {
public:
    BotManager() = default;

    void addBot(const std::shared_ptr<Player>& bot, std::unique_ptr<BotStrategy> strategy);

    void eraseBot(const std::shared_ptr<Player> &bot);

    void clear();

    Expression calculateExpression(const std::shared_ptr<Player> &bot, const std::vector<std::shared_ptr<Player>>& players, const std::vector<std::shared_ptr<Obstacle>>& obstacles);

private:
    std::unordered_map<std::shared_ptr<Player>, std::unique_ptr<BotStrategy> > bots;
};