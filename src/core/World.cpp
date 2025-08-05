#include "core/World.h"

#include "core/bot/BotFactory.h"

World::World(int playerCount, int unitsPerPlayer, int obstacleCount) {
    this->playerCount = playerCount;
    this->unitsPerPlayer = unitsPerPlayer;
    this->obstacleCount = obstacleCount;

    generatePlayers();
    generateObstacles();
    playersQueue.front()->switchCurrent();
}

void World::generatePlayers() {
    const int totalUnitCount = playerCount * unitsPerPlayer;
    players.clear();
    playersQueue = std::queue<std::shared_ptr<Player> >();
    constexpr sf::Vector2u size = {GameConstants::WIDTH, GameConstants::HEIGHT};
    for (int i = 0; i < totalUnitCount; i++) {
        bool isBot = sf::Color::Red != GameConstants::PLAYER_COLOR[i % playerCount];
        bool placed = false;
        sf::Vector2f point;
        while (!placed) {
            point = {
                Rng::getFloat(GameConstants::MIN_X, GameConstants::MAX_X),
                Rng::getFloat(GameConstants::MIN_Y, GameConstants::MAX_Y)
            };
            placed = true;
            for (const auto &p: players) {
                if (Geometry::dist(point, p->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_PLAYERS)
                    placed = false;
            }

            if (std::min(static_cast<float>(size.x) - Geometry::mapToWindow(point, size).x,
                         Geometry::mapToWindow(point, size).x) <
                GameConstants::PLAYER_WIDTH_OFFSET ||
                std::min(static_cast<float>(size.y) - Geometry::mapToWindow(point, size).y,
                         Geometry::mapToWindow(point, size).y) <
                GameConstants::PLAYER_HEIGHT_OFFSET)
                placed = false;
        }

        auto newPlayer = std::make_shared<Player>(point, GameConstants::PLAYER_COLOR[i % playerCount], GameConstants::PLAYER_RADIUS, isBot);

        if (isBot) {
            botManager.addBot(newPlayer, BotFactory::create(BotFactory::Difficulty::HARD_LINEAR));
        }

        players.push_back(newPlayer);
        playersQueue.push(players.back());
    }
}

void World::generateObstacles() {
    obstacles.clear();
    constexpr sf::Vector2u size = {GameConstants::WIDTH, GameConstants::HEIGHT};
    for (int i = 0; i < obstacleCount; ++i) {
        bool placed = false;
        sf::Vector2f point;
        while (!placed) {
            point = {
                Rng::getFloat(GameConstants::MIN_X, GameConstants::MAX_X),
                Rng::getFloat(GameConstants::MIN_Y, GameConstants::MAX_Y)
            };
            placed = true;
            for (const auto &p: players) {
                if (Geometry::dist(point, p->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_PLAYER_AND_OBSTACLE)
                    placed = false;
            }
            for (const auto &o: obstacles) {
                if (Geometry::dist(point, o->getPosition()) <
                    GameConstants::DISTANCE_BETWEEN_OBSTACLES)
                    placed = false;
            }
        }
        obstacles.push_back(std::make_unique<Obstacle>(sf::Vector2f(point)));
    }
}


void World::fireProjectile(const Expression &expr, sf::Color color) {
    if (playersQueue.empty()) return;
    auto currentPlayer = playersQueue.front();
    sf::Vector2f origin = currentPlayer->getPosition();

    activeProjectile = std::make_unique<Projectile>(expr, color, origin);

    auto collisionResult = CollisionManager::checkCollisions(
        activeProjectile->getVertices(),
        origin,
        color,
        obstacles,
        players
    );

    activeProjectile->setCollidedVertices(collisionResult.vertices);
    activeProjectile->setCenterIndex(collisionResult.centerIndex);

    activeProjectile->storeCollisionEvents(
        collisionResult.hitPlayers,
        collisionResult.hitObstacles,
        collisionResult.centerIndex
    );
}

void World::update(float dt) {
    if (!activeProjectile) return;
    activeProjectile->update(dt);

    if (!activeProjectile->isActive()) {
        activeProjectile.reset();
        nextTurn();
    }
}

void World::draw(sf::RenderTarget &target) const {
    for (const auto &obstacle: obstacles) {
        obstacle->draw(target);
    }

    for (const auto &player: players) {
        player->draw(target);
    }

    if (activeProjectile) {
        activeProjectile->draw(target);
    }
}

bool World::isProjectileActive() const {
    return activeProjectile != nullptr;
}


bool World::isGameOver() const {
    return gameOver;
}

const std::shared_ptr<Player> &World::getCurrentPlayer() const {
    return playersQueue.front();
}

void World::nextTurn() {
    const auto prevPlayer = playersQueue.front();
    prevPlayer->switchCurrent();

    playersQueue.pop();
    playersQueue.push(prevPlayer);

    while (!playersQueue.empty() && !playersQueue.front()->isAlive()) {
        playersQueue.pop();
    }

    if (playersQueue.empty()) {
        gameOver = true;
        return;
    }

    const auto newPlayer = playersQueue.front();
    if (newPlayer == prevPlayer) {
        prevPlayer->switchCurrent();
        gameOver = true;
        return;
    }
    newPlayer->switchCurrent();
}

const std::vector<std::shared_ptr<Obstacle> > &World::getObstacles() const {
    return obstacles;
}

const std::vector<std::shared_ptr<Player> > &World::getPlayers() const {
    return players;
}
