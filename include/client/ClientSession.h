#pragma once
#include <queue>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "common/NetworkMessage.h"

class ClientSession {
public:
    using MessageHandler = std::function<void(const NetworkMessage&)>;
    using DisconnectHandler = std::function<void()>;

    explicit ClientSession(boost::asio::io_context& ctx);

    void connect(const std::string& ip, uint16_t port);
    void send(const NetworkMessage& msg);
    void setMessageHandler(MessageHandler handler);
    void setDisconnectHandler(DisconnectHandler handler);


private:
    void asyncReadHeader();
    void asyncReadBody();
    void asyncWrite();

    boost::asio::io_context ctx;
    boost::asio::ip::tcp::socket socket;
    MessageHandler msgHandler;
    DisconnectHandler disconnectHandler;
    uint32_t msgSize = 0;
    std::string buf;
    std::queue<NetworkMessage> writeQueue;



};
