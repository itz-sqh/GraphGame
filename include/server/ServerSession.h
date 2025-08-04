#pragma once
#include <memory>
#include <queue>
#include <boost/asio/ip/tcp.hpp>
#include "common/NetworkMessage.h"


class ServerSession : public std::enable_shared_from_this<ServerSession> {
public:
    using ptr = std::shared_ptr<ServerSession>;

    explicit ServerSession(boost::asio::ip::tcp::socket socket);

    void start();

    void send(const NetworkMessage &msg);

    int getPlayerId() const { return playerId; }

    std::function<void(NetworkMessage)> OnMessage;
    std::function<void()> OnDisconnect;

private:
    void asyncReadHeader();

    void asyncReadBody();

    void asyncWrite();

    boost::asio::ip::tcp::socket socket;
    int playerId = -1;
    uint32_t msgSize = 0;
    std::string buf;
    std::queue<NetworkMessage> writeQueue;
};
