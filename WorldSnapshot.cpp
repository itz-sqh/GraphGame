#include "WorldSnapshot.h"

WorldSnapshot::WorldSnapshot() : projectile({}, sf::Color::White, {0, 0}) {}

WorldSnapshot::WorldSnapshot(std::vector<Player> players, std::vector<Obstacle> obstacles, bool gameOver, std::string playerInput, Projectile projectile) :
players(players), obstacles(obstacles), gameOver(gameOver), playerInput(playerInput), projectile(projectile) {}



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
