#include "core/bot/BotManager.h"


void BotManager::addBot(const std::shared_ptr<Player> &bot, std::unique_ptr<BotStrategy> strategy) {
    bots.emplace(bot, std::move(strategy));
}

void BotManager::eraseBot(const std::shared_ptr<Player> &bot) {
    bots.erase(bot);
}

Expression BotManager::calculateExpression(const std::shared_ptr<Player> &bot,
                                           const std::vector<std::shared_ptr<Player> > &players,
                                           const std::vector<std::shared_ptr<Obstacle> > &obstacles) {
    if (const auto it = bots.find(bot); it != bots.end()) {
        return it->second->calculateExpression(bot, players, obstacles);
    }
    throw std::runtime_error("Player is not a bot");
}
