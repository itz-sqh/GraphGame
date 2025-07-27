#pragma once
#include <memory>
#include <queue>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include "math/Rng.h"
#include "objects/Obstacle.h"
#include "objects/Player.h"
#include"objects/Projectile.h"
#include"math/CollisionManager.h"


class World {
public:
    World();

    void generatePlayers();

    void generateObstacles();

    void nextTurn();

    void fireProjectile(const Expression &expr, sf::Color color);

    void update(float dt);

    void draw(sf::RenderTarget &target) const;

    [[nodiscard]] bool isProjectileActive() const;

    [[nodiscard]] bool isGameOver() const;

    [[nodiscard]] const std::shared_ptr<Player> &getCurrentPlayer() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Obstacle> >& getObstacles() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Player> >& getPlayers() const;

private:
    std::vector<std::shared_ptr<Player> > players;
    std::vector<std::shared_ptr<Obstacle> > obstacles;
    std::queue<std::shared_ptr<Player> > playersQueue;

    bool gameOver = false;

    std::unique_ptr<Projectile> activeProjectile;
};
