#pragma once
#include <memory>
#include <queue>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include "core/bot/BotFactory.h"
#include "bot/BotManager.h"
#include "math/Rng.h"
#include "objects/Obstacle.h"
#include "objects/Player.h"
#include"objects/Projectile.h"
#include"math/CollisionManager.h"
#include "ConfigManager.h"


class World {
public:
    explicit World(const ConfigManager &config);

    ~World();

    void clear();

    void clearPlayers();

    void clearObstacles();

    void clearProjectile();

    void generatePlayers(const ConfigManager &config);

    void generateObstacles();

    void nextTurn();

    void fireProjectile(const Expression &expr, sf::Color color);

    void update(float dt);

    void draw(sf::RenderTarget &target) const;

    bool allPlayersHaveSameColor() const;

    [[nodiscard]] bool isProjectileActive() const;

    [[nodiscard]] bool isGameOver() const;

    [[nodiscard]] const std::shared_ptr<Player> &getCurrentPlayer() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Obstacle> > &getObstacles() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Player> > &getPlayers() const;

    [[nodiscard]] BotManager &getBotManager() { return m_botManager; }

private:
    int m_playerCount = GameConstants::PLAYER_COUNT;
    int m_unitsPerPlayer = GameConstants::UNITS_PER_PLAYER;
    int m_obstacleCount = GameConstants::OBSTACLE_COUNT;

    std::vector<std::shared_ptr<Player> > m_players;
    std::vector<std::shared_ptr<Obstacle> > m_obstacles;
    std::queue<std::shared_ptr<Player> > m_playersQueue;

    bool m_isGameOver = false;

    std::unique_ptr<Projectile> m_activeProjectile;

    BotManager m_botManager;
};
