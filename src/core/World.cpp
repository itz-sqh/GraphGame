#include "core/World.h"

World::World() {
    generatePlayers();
    generateObstacles();
}

void World::generatePlayers() {
    players.clear();
    playersQueue = std::queue<std::shared_ptr<Player>>();
    constexpr sf::Vector2u size = {GameConstants::WIDTH, GameConstants::HEIGHT};
    for (int i = 0; i < GameConstants::PLAYER_COUNT; i++) {
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
        players.push_back(
                std::make_shared<Player>(point, GameConstants::PLAYER_COLOR[i % GameConstants::PLAYER_COUNT]));
        playersQueue.push(players.back());
    }
}

void World::generateObstacles() {
    obstacles.clear();
    constexpr sf::Vector2u size = {GameConstants::WIDTH, GameConstants::HEIGHT};
    for (int i = 0; i < GameConstants::OBSTACLE_COUNT; ++i) {
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

void nextTurn() {

}

void World::fireProjectile(const Expression &expr, sf::Color color) {
    activeProjectile = std::make_unique<Projectile>(
        expr,color,getCurrentPlayer()->getPosition()
        );
}

void World::update(float dt) {
    if (!activeProjectile) return;
    activeProjectile->update(dt,obstacles,players);

    if (!activeProjectile->isActive()) {
        activeProjectile.reset();
        nextTurn();
    }

}

void World::draw(sf::RenderTarget &target) const {
    for (const auto& obstacle : obstacles) {
        obstacle->draw(target);
    }

    for (const auto& player : players) {
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
    const auto newPlayer = playersQueue.front();
    if (newPlayer == prevPlayer) {
        gameOver = true;
    }
    newPlayer->switchCurrent();
}

const std::vector<std::shared_ptr<Obstacle> >& World::getObstacles() const {
    return obstacles;
}

const std::vector<std::shared_ptr<Player> > &World::getPlayers() const {
    return players;
}








