#include "WorldSnapshot.h"

WorldSnapshot::WorldSnapshot() : projectile({}, sf::Color::White, {0, 0}) {}


WorldSnapshot::WorldSnapshot(const std::vector<std::shared_ptr<Player> > &players,
              const std::vector<std::shared_ptr<Obstacle> > &obstacles,
              bool gameOver, const std::string &playerInput,
              const std::unique_ptr<Projectile> &projectile) : gameOver(gameOver), playerInput(playerInput) {
    for (const auto& player : players) {
        this->players.emplace_back(*player);
    }
    for (const auto& obstacle : obstacles) {
        this->obstacles.emplace_back(*obstacle);
    }
    this->projectile = *projectile;
}



std::string WorldSnapshot::toString() const {
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << *this;
    return oss.str();
}

WorldSnapshot WorldSnapshot::fromString(const std::string &s) {
    WorldSnapshot snapshot;
    std::istringstream iss(s);
    boost::archive::text_iarchive ia(iss);
    ia >> snapshot;
    return snapshot;
}

void WorldSnapshot::clear() {
    gameOver = false;
    players.clear();
    obstacles.clear();
    playerInput.clear();
    projectile = Projectile({}, sf::Color::White, {0, 0});
}
