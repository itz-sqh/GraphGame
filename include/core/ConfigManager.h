#pragma once
#include "bot/BotFactory.h"
#include <fstream>
#include <iostream>

struct PlayerConfig {
    bool isBot;
    BotFactory::Difficulty difficulty;
};

class ConfigManager {
public:
    ConfigManager();

    void loadConfig();

    void saveConfig();

    void setResolution(sf::Vector2u size);

    [[nodiscard]] sf::Vector2u getResolution() const;

    void setPlayerCount(int count);

    [[nodiscard]] int getPlayerCount() const;

    void setUnitsPerPlayer(int units);

    [[nodiscard]] int getUnitsPerPlayer() const;

    void setObstacleCount(int count);

    [[nodiscard]] int getObstacleCount() const;

    void setPlayerConfig(int index, PlayerConfig config);

    [[nodiscard]] PlayerConfig getPlayerConfig(int index) const;

private:
    sf::Vector2u m_size;
    int m_playerCount = GameConstants::PLAYER_COUNT;
    int m_unitsPerPlayer = GameConstants::UNITS_PER_PLAYER;
    int m_obstacleCount = GameConstants::OBSTACLE_COUNT;
    std::vector<PlayerConfig> m_playerConfigs;
};
