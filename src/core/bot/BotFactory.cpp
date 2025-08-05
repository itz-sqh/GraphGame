#include "core/bot/BotFactory.h"

#include "core/bot/EasyLinearBotStrategy.h"
#include "core/bot/HardLinearBotStrategy.h"


std::unique_ptr<BotStrategy> BotFactory::create(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::EASY_LINEAR:
            return std::make_unique<EasyLinearBotStrategy>();
            break;
        case Difficulty::HARD_LINEAR:
            return std::make_unique<HardLinearBotStrategy>();
            break;
        default:
            return std::make_unique<EasyLinearBotStrategy>();
            break;
    }
}
