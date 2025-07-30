#pragma once


#include<vector>

#include "objects/Obstacle.h"
#include "objects/Player.h"
#include "objects/Projectile.h"
#include <boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include"Serialization.h"
#include<boost/serialization/vector.hpp>
#include<boost/serialization/string.hpp>

template<typename Archive>
void serialize(Archive &ar, sf::Vector2f &vec, const unsigned int version) {
    ar & vec.x;
    ar & vec.y;
}

template<typename Archive>
void serialize(Archive &ar, sf::Color &color, const unsigned int version) {
    ar & color.r;
    ar & color.g;
    ar & color.b;
    ar & color.a;
}

struct WorldSnapshot {
    WorldSnapshot();

    WorldSnapshot(std::vector<Player> players, std::vector<Obstacle> obstacles, bool gameOver, std::string playerInput, Projectile projectile);

    bool gameOver{};

    std::vector<Player> players;
    std::vector<Obstacle> obstacles;

    std::string playerInput;
    Projectile projectile;

    void clear();

    template<typename Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & gameOver & players & obstacles & playerInput & projectile;
    }

    [[nodiscard]] std::string toString() const;

    static WorldSnapshot fromString(const std::string &s);
};
