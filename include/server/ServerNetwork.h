#pragma once
#include <boost/asio.hpp>
#include <unordered_map>
#include "ServerSession.h"

class ServerNetwork {
public:
    ServerNetwork(boost::asio::io_context& ctx, uint16_t port);

    void start();
    void stop();
    void broadcast(const NetworkMessage& message);
    void sendToPlayer(int playerId, const NetworkMessage& message);

    void registerSessionHandler(std::function<void(ServerSession::ptr)> handler);
    void registerMessageHandler(std::function<void(ServerSession::ptr, NetworkMessage)> handler);

private:
    void acceptConnection();

    boost::asio::io_context& ctx;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unordered_map<int, ServerSession::ptr> sessions;
    std::vector<std::function<void(ServerSession::ptr)>> sessionHandlers;
    std::vector<std::function<void(ServerSession::ptr, NetworkMessage)>> messageHandlers;
};