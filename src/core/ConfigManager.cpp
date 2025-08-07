#include "core/ConfigManager.h"


ConfigManager::ConfigManager() {
    m_size = {GameConstants::WIDTH, GameConstants::HEIGHT};
    m_playerCount = GameConstants::PLAYER_COUNT;
    m_unitsPerPlayer = GameConstants::UNITS_PER_PLAYER;
    m_obstacleCount = GameConstants::OBSTACLE_COUNT;

    m_playerConfigs.resize(m_playerCount);
    for (auto &config: m_playerConfigs) {
        config.isBot = true;
        config.difficulty = BotFactory::Difficulty::EASY_LINEAR;
    }
    m_playerConfigs.front().isBot = false;
}

void ConfigManager::loadConfig() {
    std::ifstream configFile("config.cfg");
    if (!configFile.is_open()) {
        std::cerr << "Using default configuration\n";
        return;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        size_t delimiter = line.find('=');
        if (delimiter == std::string::npos) continue;

        std::string key = line.substr(0, delimiter);
        std::string value = line.substr(delimiter + 1);

        if (key == "resolution") {
            size_t xPos = value.find('x');
            if (xPos != std::string::npos) {
                try {
                    unsigned int w = std::stoul(value.substr(0, xPos));
                    unsigned int h = std::stoul(value.substr(xPos + 1));
                    GameConstants::WIDTH = w;
                    GameConstants::HEIGHT = h;
                    m_size = {w, h};
                } catch (...) {
                    std::cerr << "Invalid resolution format\n";
                }
            }
        } else if (key == "playerCount") {
            try {
                int count = std::stoi(value);
                setPlayerCount(count);
            } catch (...) {
                std::cerr << "Invalid player count\n";
            }
        } else if (key == "unitsPerPlayer") {
            try {
                m_unitsPerPlayer = std::stoi(value);
            } catch (...) {
                std::cerr << "Invalid units per player\n";
            }
        } else if (key == "obstacleCount") {
            try {
                m_obstacleCount = std::stoi(value);
            } catch (...) {
                std::cerr << "Invalid obstacle count\n";
            }
        } else if (key.find("player") == 0) {
            try {
                int index = std::stoi(key.substr(6));
                if (index >= 0 && index < m_playerConfigs.size()) {
                    size_t commaPos = value.find(',');
                    if (commaPos != std::string::npos) {
                        bool isBot = std::stoi(value.substr(0, commaPos)) != 0;
                        int diff = std::stoi(value.substr(commaPos + 1));
                        m_playerConfigs[index] = {isBot, static_cast<BotFactory::Difficulty>(diff)};
                    }
                }
            } catch (...) {
                std::cerr << "Invalid player config\n";
            }
        }
    }
}


void ConfigManager::saveConfig() {
    std::ofstream configFile("config.cfg");
    if (!configFile.is_open()) {
        std::cerr << "Could not save config file\n";
        return;
    }

    configFile << "resolution=" << m_size.x << "x" << m_size.y << "\n";
    configFile << "playerCount=" << m_playerCount << "\n";
    configFile << "unitsPerPlayer=" << m_unitsPerPlayer << "\n";
    configFile << "obstacleCount=" << m_obstacleCount << "\n";

    for (size_t i = 0; i < m_playerConfigs.size(); ++i) {
        configFile << "player" << i << "="
                << m_playerConfigs[i].isBot << ","
                << static_cast<int>(m_playerConfigs[i].difficulty) << "\n";
    }
}


void ConfigManager::setPlayerCount(int count) {
    if (count < 0) return;
    m_playerConfigs.resize(count);
    for (int i = m_playerCount; i < count; ++i) {
        m_playerConfigs[i] = {true, BotFactory::Difficulty::EASY_LINEAR};
    }
    m_playerCount = count;
}

PlayerConfig ConfigManager::getPlayerConfig(int index) const {
    return m_playerConfigs[index];
}

void ConfigManager::setObstacleCount(int count) {
    if (count < 0) return;
    m_obstacleCount = count;
}

void ConfigManager::setPlayerConfig(int index, PlayerConfig config) {
    if (index < 0 || index > m_playerConfigs.size()) return;
    m_playerConfigs[index] = config;
}

void ConfigManager::setResolution(sf::Vector2u size) {
    this->m_size = size;
}

void ConfigManager::setUnitsPerPlayer(int units) {
    if (units < 0) return;
    m_unitsPerPlayer = units;
}

int ConfigManager::getObstacleCount() const {
    return m_obstacleCount;
}

int ConfigManager::getPlayerCount() const {
    return m_playerCount;
}

sf::Vector2u ConfigManager::getResolution() const {
    return m_size;
}

int ConfigManager::getUnitsPerPlayer() const {
    return m_unitsPerPlayer;
}
