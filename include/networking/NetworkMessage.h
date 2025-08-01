#pragma once
#include<string>
#include<ostream>
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include"WorldSnapshot.h"

enum MessageType : uint8_t {
    PLAYER_INPUT = 0,
    WORLD_SNAPSHOT = 1,
};




struct NetworkMessage {
    MessageType type;
    std::variant<std::string, WorldSnapshot> data;


    static NetworkMessage create_player_input(const std::string &input);

    static NetworkMessage create_world_snapshot(const WorldSnapshot &snapshot);

    template<typename T>
    const T *get() const {
        return std::get_if<T>(&data);
    }
};


namespace MessageSerializer {
    std::string serialize(const NetworkMessage& msg);

    NetworkMessage deserialize(const std::string &data);
}