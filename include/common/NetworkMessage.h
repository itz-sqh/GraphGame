#pragma once
#include<string>
#include<ostream>
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include"WorldSnapshot.h"

enum MessageType : uint8_t {
    PLAYER_INPUT = 0,
    WORLD_SNAPSHOT = 1,
    PLAYER_ASSIGNMENT = 2
};


struct NetworkMessage {
    MessageType type;
    int playerId = -1;
    std::variant<WorldSnapshot, std::string> data;

    template<typename Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar & type & playerId & data;
    }

    template<typename T>
    [[nodiscard]] bool is() const {
        return std::holds_alternative<T>(data);
    }

    template<typename T>
    const T &get() const {
        return std::get<T>(data);
    }

    template<typename T>
    const T *getIf() const noexcept {
        return std::get_if<T>(data);
    }


    static NetworkMessage CreatePlayerAssignment(int playerId);

    static NetworkMessage CreatePlayerInput(const std::string &input);

    static NetworkMessage CreateWorldSnapshot(const WorldSnapshot &snapshot);
};


namespace MessageSerializer {
    std::string serialize(const NetworkMessage &msg);

    NetworkMessage deserialize(const std::string &data);
}
