#pragma once
#include "BotStrategy.h"
#include "core/bot/EasyLinearBotStrategy.h"
#include "core/bot/HardLinearBotStrategy.h"
#include <memory>

class BotFactory {
public:
    enum class Difficulty { EASY_LINEAR, HARD_LINEAR };

    static std::unique_ptr<BotStrategy> create(Difficulty difficulty);
};