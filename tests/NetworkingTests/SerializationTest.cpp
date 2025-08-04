#define BOOST_TEST_MODULE SerializationTest
#include <boost/test/unit_test.hpp>
#include "common/NetworkMessage.h"
#include "core/World.h"


BOOST_AUTO_TEST_SUITE(SerializationTest)

    BOOST_AUTO_TEST_CASE(player_input_test) {
    {
        std::string playerInput = "sin(x)";
        auto msg = NetworkMessage::CreatePlayerInput(playerInput);

        std::string serialized = MessageSerializer::serialize(msg);

        auto observed = MessageSerializer::deserialize(serialized);


        BOOST_CHECK_EQUAL(observed.type, MessageType::PLAYER_INPUT);

        BOOST_CHECK_EQUAL(observed.get<std::string>(), playerInput);
    }
    {
        std::string playerInput = "(x)+(sin(x)+cos(x))*e^(-x^2)";
        auto msg = NetworkMessage::CreatePlayerInput(playerInput);

        std::string serialized = MessageSerializer::serialize(msg);

        auto observed = MessageSerializer::deserialize(serialized);


        BOOST_CHECK_EQUAL(observed.type, MessageType::PLAYER_INPUT);

        BOOST_CHECK_EQUAL(observed.get<std::string>(), playerInput);
    }
    {
        std::string playerInput = "e^-x^2*sin(x)+x*cos(x)+1-1+1-1";
        auto msg = NetworkMessage::CreatePlayerInput(playerInput);

        std::string serialized = MessageSerializer::serialize(msg);

        auto observed = MessageSerializer::deserialize(serialized);


        BOOST_CHECK_EQUAL(observed.type, MessageType::PLAYER_INPUT);

        BOOST_CHECK_EQUAL(observed.get<std::string>(), playerInput);
    }
    {
        std::string playerInput = "x";
        auto msg = NetworkMessage::CreatePlayerInput(playerInput);

        std::string serialized = MessageSerializer::serialize(msg);

        auto observed = MessageSerializer::deserialize(serialized);


        BOOST_CHECK_EQUAL(observed.type, MessageType::PLAYER_INPUT);

        BOOST_CHECK_EQUAL(observed.get<std::string>(), playerInput);
    }
    {
        std::string playerInput = "0";
        auto msg = NetworkMessage::CreatePlayerInput(playerInput);

        std::string serialized = MessageSerializer::serialize(msg);

        auto observed = MessageSerializer::deserialize(serialized);

        BOOST_CHECK_EQUAL(observed.type, MessageType::PLAYER_INPUT);

        BOOST_CHECK_EQUAL(observed.get<std::string>(), playerInput);
    }
}

BOOST_AUTO_TEST_CASE(world_snapshot_test) {
    const uint32_t seed = 42069;
    for (int i = 0 ; i < 10; i++) {
        Rng::setSeed(seed+i);

        World world;

        const auto& players = world.getPlayers();
        const auto& obstacles = world.getObstacles();

        bool gameOver = Rng::getInt(0,1);

        std::string playerInput = "e^-x^2*sin(x)+x*cos(x)";

        auto expr = ExpressionParser::parse(playerInput).value();

        world.setProjectile(expr, sf::Color::Red, {0,0});

        const auto& projectile = world.getProjectile();

        WorldSnapshot snapshot(players,obstacles,gameOver,playerInput,projectile);

        auto msg = NetworkMessage::CreateWorldSnapshot(snapshot);

        std::string serialized = MessageSerializer::serialize(msg);

        auto deserialized = MessageSerializer::deserialize(serialized);

        BOOST_CHECK_EQUAL(deserialized.type, MessageType::WORLD_SNAPSHOT);

        auto* observed = deserialized.getIf<WorldSnapshot>();

        BOOST_REQUIRE(observed != nullptr);

        BOOST_CHECK_EQUAL(observed->gameOver, snapshot.gameOver);
        BOOST_CHECK_EQUAL(observed->playerInput, snapshot.playerInput);

        BOOST_CHECK_EQUAL(observed->players.size(), players.size());
        for (size_t j = 0; j < players.size(); j++) {
            BOOST_CHECK_EQUAL(observed->players[j], *players[j]);

        }

        BOOST_CHECK_EQUAL(observed->obstacles.size(), obstacles.size());
        for (size_t j = 0; j < players.size(); j++) {
            BOOST_CHECK_EQUAL(observed->obstacles[j], *obstacles[j]);

        }
    }
}




BOOST_AUTO_TEST_SUITE_END()


