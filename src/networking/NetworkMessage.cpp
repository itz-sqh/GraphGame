#include "networking/NetworkMessage.h"

std::string serialize(const NetworkMessage& msg) {
    std::ostringstream oss;
    boost::archive::text_oarchive ar(oss);

    ar << static_cast<uint8_t>(msg.type);

    switch (msg.type) {
        case PLAYER_INPUT:
            ar << *std::get_if<std::string>(&msg.data);
            break;
        case WORLD_SNAPSHOT:
            ar << *std::get_if<WorldSnapshot>(&msg.data);
            break;
        default:
            throw std::runtime_error("Unknown message type for serialization");
    }

    return oss.str();
}

NetworkMessage deserialize(const std::string &data) {
    std::istringstream iss(data);
    boost::archive::text_iarchive ar(iss);

    uint8_t type_byte;
    ar >> type_byte;

    switch (static_cast<MessageType>(type_byte)) {
        case PLAYER_INPUT: {
            std::string input;
            ar >> input;
            return NetworkMessage::create_player_input(input);
        }
        case WORLD_SNAPSHOT: {
            WorldSnapshot snap;
            ar >> snap;
            return NetworkMessage::create_world_snapshot(snap);
        }
        default:
            throw std::runtime_error("Unknown message type for deserialization");
    }
}

