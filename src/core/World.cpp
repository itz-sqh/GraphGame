#include "core/World.h"


World::World(const ConfigManager &config) {
    this->m_playerCount = config.getPlayerCount();
    this->m_unitsPerPlayer = config.getUnitsPerPlayer();
    this->m_obstacleCount = config.getObstacleCount();

    generatePlayers(config);
    generateObstacles();
    m_playersQueue.front()->switchCurrent();
}

void World::generatePlayers(const ConfigManager &config) {
    const int totalUnitCount = m_playerCount * m_unitsPerPlayer;
    m_players.clear();
    m_playersQueue = std::queue<std::shared_ptr<Player> >();
    for (int i = 0; i < totalUnitCount; i++) {
        bool placed = false;

        sf::Vector2f point;
        while (!placed) {
            point = {
                Rng::getFloat(GameConstants::MIN_X, GameConstants::MAX_X),
                Rng::getFloat(GameConstants::MIN_Y, GameConstants::MAX_Y)
            };
            placed = true;
            for (const auto &p: m_players) {
                if (Geometry::dist(point, p->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_PLAYERS)
                    placed = false;
            }

            if (point.x < GameConstants::MIN_X + GameConstants::PLAYER_WIDTH_OFFSET ||
                point.x > GameConstants::MAX_X - GameConstants::PLAYER_WIDTH_OFFSET ||
                point.y < GameConstants::MIN_Y + GameConstants::PLAYER_HEIGHT_OFFSET ||
                point.y > GameConstants::MAX_Y - GameConstants::PLAYER_HEIGHT_OFFSET) {
                placed = false;
            }
        }
        bool isBot = config.getPlayerConfig(i % m_playerCount).isBot;
        BotFactory::Difficulty difficulty = config.getPlayerConfig(i % m_playerCount).difficulty;
        auto newPlayer = std::make_shared<Player>(point, GameConstants::PLAYER_COLOR[i % m_playerCount],
                                                  GameConstants::PLAYER_RADIUS, isBot);

        if (isBot) {
            m_botManager.addBot(newPlayer, BotFactory::create(difficulty));
        }

        m_players.push_back(newPlayer);
        m_playersQueue.push(m_players.back());
    }
}

void World::generateObstacles() {
    m_obstacles.clear();
    for (int i = 0; i < m_obstacleCount; ++i) {
        bool placed = false;
        sf::Vector2f point;
        while (!placed) {
            point = {
                Rng::getFloat(GameConstants::MIN_X, GameConstants::MAX_X),
                Rng::getFloat(GameConstants::MIN_Y, GameConstants::MAX_Y)
            };
            placed = true;
            for (const auto &p: m_players) {
                if (Geometry::dist(point, p->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE)
                    placed = false;
            }
            for (const auto &o: m_obstacles) {
                if (Geometry::dist(point, o->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_OBSTACLES)
                    placed = false;
            }
        }
        m_obstacles.push_back(std::make_unique<Obstacle>(sf::Vector2f(point)));
    }
}


void World::fireProjectile(const Expression &expr, sf::Color color) {
    if (m_playersQueue.empty()) return;
    auto currentPlayer = m_playersQueue.front();
    sf::Vector2f origin = currentPlayer->getPosition();

    m_activeProjectile = std::make_unique<Projectile>(expr, color, origin);

    auto collisionResult = CollisionManager::checkCollisions(
        m_activeProjectile->getVertices(),
        origin,
        color,
        m_obstacles,
        m_players
    );

    m_activeProjectile->setCollidedVertices(collisionResult.vertices);
    m_activeProjectile->setCenterIndex(collisionResult.centerIndex);

    m_activeProjectile->storeCollisionEvents(
        collisionResult.hitPlayers,
        collisionResult.hitObstacles,
        collisionResult.centerIndex
    );
}

void World::update(float dt) {
    if (!m_activeProjectile) return;
    m_activeProjectile->update(dt);

    if (!m_activeProjectile->isActive()) {
        m_activeProjectile.reset();
        nextTurn();
    }
}

void World::draw(sf::RenderTarget &target) const {
    for (const auto &obstacle: m_obstacles) {
        obstacle->draw(target);
    }

    for (const auto &player: m_players) {
        player->draw(target);
    }

    if (m_activeProjectile) {
        m_activeProjectile->draw(target);
    }
}

bool World::isProjectileActive() const {
    return m_activeProjectile != nullptr;
}


bool World::isGameOver() const {
    return m_isGameOver;
}

const std::shared_ptr<Player> &World::getCurrentPlayer() const {
    return m_playersQueue.front();
}

void World::nextTurn() {
    if (m_playersQueue.empty() || allPlayersHaveSameColor()) {
        m_isGameOver = true;
        return;
    }
    const auto prevPlayer = m_playersQueue.front();
    prevPlayer->switchCurrent();

    m_playersQueue.pop();
    m_playersQueue.push(prevPlayer);

    while (!m_playersQueue.empty() && !m_playersQueue.front()->isAlive()) {
        m_playersQueue.pop();
    }

    if (m_playersQueue.empty() || allPlayersHaveSameColor()) {
        m_isGameOver = true;
        return;
    }

    m_playersQueue.front()->switchCurrent();
}

const std::vector<std::shared_ptr<Obstacle> > &World::getObstacles() const {
    return m_obstacles;
}

const std::vector<std::shared_ptr<Player> > &World::getPlayers() const {
    return m_players;
}


bool World::allPlayersHaveSameColor() const {
    if (m_playersQueue.empty()) return true;

    const sf::Color firstColor = m_playersQueue.front()->getColor();

    auto tmp = m_playersQueue;
    while (!tmp.empty()) {
        if (tmp.front()->getColor() != firstColor) {
            return false;
        }
        tmp.pop();
    }
    return true;
}

void World::clear() {
    clearPlayers();
    clearObstacles();
    clearProjectile();
    m_botManager.clear();
    m_isGameOver = false;
}

void World::clearObstacles() {
    m_obstacles.clear();
}

void World::clearPlayers() {
    m_players.clear();
    while (!m_playersQueue.empty())
        m_playersQueue.pop();
}

void World::clearProjectile() {
    m_activeProjectile.reset();
}

World::~World() {
    clear();
}
